#include <array>
#include <bit>
#include <cstddef>
#include <limits>

#include "gtest/gtest.h"
#include "integral_aliases.hpp"
#include "max2.hpp"
#include "min2.hpp"
#include "signed_integral_aliases.hpp"
#include "sparse_table/st_make.hpp"
#include "sparse_table/st_required_buffer_size.hpp"

template <typename T>
class SparseTableMakeTypedTest : public ::testing::Test
{
};

using SparseTableMakeValueTypes =
    ::testing::Types<u8, u16, u32, u64, i8, i16, i32, i64>;
TYPED_TEST_SUITE(SparseTableMakeTypedTest, SparseTableMakeValueTypes);

TYPED_TEST(SparseTableMakeTypedTest, BuildsLevelsWithoutChangingSource)
{
    using T = TypeParam;
    const std::array<T, 5> source{5, 2, 7, 1, 4};
    const auto original = source;
    const auto verify = [&]<typename Op>(Op, const std::array<T, 16>& expected)
    {
        std::array<T, 16> buffer{};
        buffer.fill(99);
        const auto table = st_make<T, u8, Op>(source.data(), 5, buffer.data());
        EXPECT_EQ(table.x, buffer.data());
        EXPECT_EQ(table.size, 5);
        EXPECT_EQ(buffer, expected);
        EXPECT_EQ(source, original);
    };
    verify(min2, {5, 2, 7, 1, 4, 2, 2, 1, 1, 99, 1, 1, 99, 99, 99, 99});
    verify(max2, {5, 2, 7, 1, 4, 5, 7, 7, 4, 99, 7, 7, 99, 99, 99, 99});
}

TEST(SparseTable, MakesEmptyTable)
{
    const auto table = st_make<int, u8, decltype(min2)>(nullptr, 0, nullptr);
    EXPECT_EQ(table.x, nullptr);
    EXPECT_EQ(table.size, 0);
}

TEST(SparseTable, MakesSingleElementTable)
{
    const int source = -7;
    std::array<int, 2> buffer{0, 99};
    const auto table =
        st_make<int, unsigned, decltype(min2)>(&source, 1, buffer.data());
    EXPECT_EQ(table.size, 1);
    EXPECT_EQ(buffer, (std::array<int, 2>{-7, 99}));
}

TEST(SparseTable, MakesMaximumSmallIndexSize)
{
    constexpr u8 n = std::numeric_limits<u8>::max();
    std::array<int, n> source{};
    for (u8 i = 0; i != n; ++i)
    {
        source.at(i) = i;
    }
    std::array<int, st_required_buffer_size(n) + 1> buffer{};
    buffer.fill(-1);
    const auto table =
        st_make<int, u8, decltype(max2)>(source.data(), n, buffer.data());
    EXPECT_EQ(table.size, n);
    for (std::size_t level = 0; level != std::bit_width(n); ++level)
    {
        const std::size_t width = std::size_t{1} << level;
        for (std::size_t i = 0; i != n - width + 1; ++i)
        {
            EXPECT_EQ(buffer.at(level * n + i), i + width - 1);
        }
    }
    EXPECT_EQ(buffer.back(), -1);
}

TEST(SparseTable, MakesAtCompileTime)
{
    static_assert(
        []
        {
            const int source[]{3, 1, 2};
            int buffer[6]{};
            const auto table =
                st_make<int, unsigned, decltype(min2)>(source, 3, buffer);
            return table.size == 3 && table.x[3] == 1 && table.x[4] == 1;
        }());
}
