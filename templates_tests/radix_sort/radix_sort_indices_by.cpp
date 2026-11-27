#include "radix_sort/radix_sort_indices_by.hpp"

#include <algorithm>
#include <array>
#include <bit>
#include <limits>
#include <numeric>
#include <random>
#include <type_traits>
#include <vector>

#include "gtest/gtest.h"

template <u32 bits, u8 digit_bits, typename I, typename Proj>
concept CanRadixSortIndices = requires(I* data, Proj proj) {
    radix_sort_indices_by<bits, digit_bits>(data, 1, proj);
};

using ByteKey = signed char (*)(u16);
static_assert(CanRadixSortIndices<8, 10, u16, ByteKey>);
static_assert(!CanRadixSortIndices<9, 10, u16, ByteKey>);
static_assert(!CanRadixSortIndices<8, 0, u16, ByteKey>);
static_assert(!CanRadixSortIndices<8, 10, int, ByteKey>);
static_assert(!CanRadixSortIndices<8, 10, u16, float (*)(u16)>);

TEST(RadixSortIndicesBy, FullWidthUsesDefaultDigitWidth)
{
    const std::array<u64, 5> keys{u64{1} << 63, 1, 0, u64{1} << 40, 1};
    std::array<u32, 5> indices{0, 1, 2, 3, 4};

    radix_sort_indices_by<64>(
        indices.data(),
        indices.size(),
        [&](u32 i) { return keys.at(i); });

    EXPECT_EQ(indices, (std::array<u32, 5>{2, 1, 4, 3, 0}));
}

TEST(RadixSortIndicesBy, LowBitsIgnoreHigherBitsAndPreserveTies)
{
    const std::array<u64, 5> keys{0xF01, 0x002, 0x103, 0xE01, 0x100};
    std::array<u32, 5> indices{0, 1, 2, 3, 4};

    radix_sort_indices_by<8, 4, SortOrder::Ascending, 5>(
        indices.data(),
        indices.size(),
        [&](u32 i) { return keys.at(i); });

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

    radix_sort_indices_by<37, 5>(
        indices.data(),
        indices.size(),
        [&](u32 i) { return keys.at(i); });

    EXPECT_EQ(indices, (std::array<u32, 4>{2, 3, 1, 0}));
}

TEST(RadixSortIndicesBy, ZeroKeyBitsLeaveInputUntouched)
{
    std::array<u32, 3> indices{2, 0, 1};

    radix_sort_indices_by<0>(
        indices.data(),
        indices.size(),
        [](u32 i) { return i; });

    EXPECT_EQ(indices, (std::array<u32, 3>{2, 0, 1}));
}

TEST(RadixSortIndicesBy, TrivialInputsDoNotInvokeProjection)
{
    u32 calls = 0;

    auto proj = [&](u32 i)
    {
        ++calls;
        return i;
    };
    u32 one = 17;
    radix_sort_indices_by<25>(static_cast<u32*>(nullptr), 0, proj);
    radix_sort_indices_by<25>(&one, 1, proj);
    std::array<u32, 2> pair{1, 0};
    radix_sort_indices_by<0>(pair.data(), 2, proj);
    EXPECT_EQ(one, 17u);
    EXPECT_EQ(pair, (std::array<u32, 2>{1, 0}));
    EXPECT_EQ(calls, 0);
}

TEST(RadixSortIndicesBy, CounterWidthBoundaries)
{
    auto check = []<u32 capacity>()
    {
        std::vector<u32> indices(capacity);
        std::iota(indices.begin(), indices.end(), 17);
        const auto expected = indices;

        radix_sort_indices_by<8, 8, SortOrder::Ascending, capacity>(
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

        radix_sort_indices_by<2, 2, SortOrder::Ascending, 6>(
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

TEST(RadixSortIndicesBy, MatchesStableSortOfProjectedKeys)
{
    auto check = []<typename Key, u32 bits, u8 digit_bits>()
    {
        using U = std::make_unsigned_t<Key>;
        std::mt19937_64 rng{3471};
        std::array<Key, 64> keys{};
        for (auto& key : keys) key = std::bit_cast<Key>(static_cast<U>(rng()));
        keys.at(0) = std::numeric_limits<Key>::lowest();
        keys.at(1) = std::numeric_limits<Key>::max();
        keys.at(2) = 0;
        keys.at(3) = keys.at(0);
        // Differ only outside the selected bits.
        if constexpr (bits < sizeof(Key) * 8)
        {
            keys.at(4) = std::bit_cast<Key>(static_cast<U>(U{1} << bits));
        }

        std::array<u16, 128> input{};
        std::iota(input.begin(), input.end(), u16{0});
        std::shuffle(input.begin(), input.end(), rng);
        auto proj = [&](u16 index) -> const Key&
        {
            return keys.at(index % keys.size());
        };
        auto reference_key = [&](u16 index)
        {
            if constexpr (bits == sizeof(Key) * 8)
            {
                return proj(index);
            }
            else
            {
                return static_cast<U>(
                    static_cast<U>(proj(index)) & ((U{1} << bits) - 1));
            }
        };
        auto compare = [&]<SortOrder order>(auto cmp)
        {
            auto actual = input, expected = input;
            std::ranges::stable_sort(expected, cmp, reference_key);
            radix_sort_indices_by<bits, digit_bits, order>(
                actual.data(),
                actual.size(),
                proj);
            EXPECT_EQ(actual, expected);
        };
        compare.template operator()<SortOrder::Ascending>(std::less{});
        compare.template operator()<SortOrder::Descending>(std::greater{});
    };

    check.template operator()<signed char, 8, 10>();
    check.template operator()<int32_t, 32, 10>();
    check.template operator()<int32_t, 25, 10>();
    check.template operator()<int64_t, 64, 17>();
    check.template operator()<u64, 37, 5>();
}

TEST(RadixSortIndicesBy, StableDescendingHighField)
{
    const u64 keys[]{0x1200000009, 0x0200000003, 0x1200000001, 0x1000000004};
    u32 indices[]{2, 1, 0, 3};
    radix_sort_indices_by<32, 7, SortOrder::Descending, 4, 32>(
        indices,
        4,
        [&](u32 i) { return keys[i]; });
    EXPECT_TRUE(std::ranges::equal(indices, std::array<u32, 4>{2, 0, 3, 1}));
}
