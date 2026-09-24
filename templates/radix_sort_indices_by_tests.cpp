#include <array>
#include <limits>
#include <numeric>
#include <vector>

#include "gtest/gtest.h"
#include "radix_sort_indices_by.hpp"

TEST(RadixSortIndicesBy, DefaultsToFullKeyWidth)
{
    const std::array<u64, 5> keys{u64{1} << 63, 1, 0, u64{1} << 40, 1};
    std::array<u32, 5> indices{0, 1, 2, 3, 4};

    radix_sort_indices_by<5>(
        indices.data(),
        indices.size(),
        [&](u32 i) { return keys[i]; });

    EXPECT_EQ(indices, (std::array<u32, 5>{2, 1, 4, 3, 0}));
}

TEST(RadixSortIndicesBy, ExplicitPassesIgnoreHigherBitsAndPreserveTies)
{
    const std::array<u64, 5> keys{0xF01, 0x002, 0x103, 0xE01, 0x100};
    std::array<u32, 5> indices{0, 1, 2, 3, 4};

    radix_sort_indices_by<4, 2, 5>(
        indices.data(),
        indices.size(),
        [&](u32 i) { return keys[i]; });

    EXPECT_EQ(indices, (std::array<u32, 5>{4, 0, 3, 1, 2}));
}

TEST(RadixSortIndicesBy, EightPassesCoverThirtySevenBits)
{
    const std::array<u64, 4> keys{
        (u64{81} << 30) | 999'999'999,
        (u64{1} << 30) | 1'000'000'000,
        (u64{1} << 30) | 1,
        (u64{1} << 30) | 10};
    std::array<u32, 4> indices{0, 1, 2, 3};

    radix_sort_indices_by<5, 8>(
        indices.data(),
        indices.size(),
        [&](u32 i) { return keys[i]; });

    EXPECT_EQ(indices, (std::array<u32, 4>{2, 3, 1, 0}));
}

TEST(RadixSortIndicesBy, ZeroPassesLeaveInputUntouched)
{
    std::array<u32, 3> indices{2, 0, 1};

    radix_sort_indices_by<8, 0>(
        indices.data(),
        indices.size(),
        [](u32 i) { return i; });

    EXPECT_EQ(indices, (std::array<u32, 3>{2, 0, 1}));
}

TEST(RadixSortIndicesBy, EmptyInputDoesNotInvokeProjection)
{
    u32 calls = 0;

    radix_sort_indices_by<5, 8>(
        static_cast<u32*>(nullptr),
        0,
        [&](u32 i) -> u64
        {
            ++calls;
            return i;
        });

    EXPECT_EQ(calls, 0);
}

TEST(RadixSortIndicesBy, CounterWidthBoundaries)
{
    auto check = []<u32 capacity>()
    {
        std::vector<u32> indices(capacity);
        std::iota(indices.begin(), indices.end(), 17);
        const auto expected = indices;

        radix_sort_indices_by<8, 1, capacity>(
            indices.data(),
            capacity,
            [](u32) { return 0u; });

        EXPECT_EQ(indices, expected);
    };

    check.template operator()<255>();
    check.template operator()<256>();
    check.template operator()<65'535>();
    check.template operator()<65'536>();
    check.template operator()<255>();
}

TEST(RadixSortIndicesBy, IndexWidthsPreserveValuesAndTies)
{
    auto check = []<typename I>()
    {
        std::array<I, 6> indices{std::numeric_limits<I>::max(), 3, 0, 7, 2, 1};
        const std::array<I, 6>
            expected{0, 1, 2, std::numeric_limits<I>::max(), 3, 7};

        radix_sort_indices_by<2, 1, 6>(
            indices.data(),
            indices.size(),
            [](I i) { return static_cast<u32>(i & 3); });

        EXPECT_EQ(indices, expected);
    };

    check.template operator()<u8>();
    check.template operator()<u16>();
    check.template operator()<u32>();
    check.template operator()<u64>();
    check.template operator()<u16>();
}
