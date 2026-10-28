#include <algorithm>
#include <array>
#include <cstddef>
#include <functional>
#include <limits>

#include "gtest/gtest.h"
#include "integral_aliases.hpp"
#include "max2.hpp"
#include "min2.hpp"
#include "signed_integral_aliases.hpp"
#include "sparse_table/st_make.hpp"
#include "sparse_table/st_range.hpp"
#include "sparse_table/st_required_buffer_size.hpp"

namespace
{
struct Left
{
    constexpr int operator()(int left, int /*right*/) const noexcept
    {
        return left;
    }
};
}  // namespace

template <typename T>
class SparseTableRangeTypedTest : public ::testing::Test
{
};

using SparseTableRangeValueTypes =
    ::testing::Types<u8, u16, u32, u64, i8, i16, i32, i64>;
TYPED_TEST_SUITE(SparseTableRangeTypedTest, SparseTableRangeValueTypes);

TYPED_TEST(SparseTableRangeTypedTest, AllRangesMatchReference)
{
    using T = TypeParam;
    std::array<T, 33> source{};
    for (std::size_t i = 0; i != source.size(); ++i)
    {
        source.at(i) = static_cast<T>((i * 17 + 5) % 31);
    }
    source.at(4) = std::numeric_limits<T>::lowest();
    source.at(12) = std::numeric_limits<T>::max();
    const auto verify = [&]<typename Op>(Op, auto op)
    {
        std::array<T, st_required_buffer_size(source.size())> buffer{};
        for (u8 n = 1; n != source.size() + 1; ++n)
        {
            const auto table =
                st_make<T, u8, Op>(source.data(), n, buffer.data());
            for (u8 begin = 0; begin != n; ++begin)
            {
                T expected = source.at(begin);
                for (u8 i = begin; i != n; ++i)
                {
                    expected = static_cast<T>(op(expected, source.at(i)));
                    EXPECT_EQ(st_range(table, begin, i + 1), expected)
                        << "n=" << +n << " begin=" << +begin
                        << " end=" << i + 1;
                }
            }
        }
    };
    verify(min2, [](T a, T b) { return std::min(a, b); });
    verify(max2, [](T a, T b) { return std::max(a, b); });
    verify(std::bit_and<>{}, std::bit_and<>{});
}

TEST(SparseTable, QueriesMaximumSmallIndexSize)
{
    constexpr u8 n = std::numeric_limits<u8>::max();
    std::array<int, n> source{};
    for (u8 i = 0; i != n; ++i)
    {
        source.at(i) = i;
    }
    std::array<int, st_required_buffer_size(n)> buffer{};
    const auto table =
        st_make<int, u8, decltype(max2)>(source.data(), n, buffer.data());
    EXPECT_EQ(st_range(table, 0, 255), 254);
    EXPECT_EQ(st_range(table, 127, 255), 254);
    EXPECT_EQ(st_range(table, 254, 255), 254);
    EXPECT_EQ(st_range(table, 0, 128), 127);
}

TEST(SparseTable, PreservesNoncommutativeOrder)
{
    const int source[]{9, 3, 7, 1, 5};
    int buffer[15]{};
    const auto table = st_make<int, unsigned, Left>(source, 5, buffer);
    EXPECT_EQ(st_range(table, 0, 5), 9);
    EXPECT_EQ(st_range(table, 1, 4), 3);
    EXPECT_EQ(st_range(table, 2, 5), 7);
}

TEST(SparseTable, QueriesAtCompileTime)
{
    static_assert(
        []
        {
            const int source[]{3, -1, 2};
            int buffer[6]{};
            const auto table =
                st_make<int, unsigned, decltype(min2)>(source, 3, buffer);
            return st_range(table, 0, 3) == -1 && st_range(table, 2, 3) == 2;
        }());
}
