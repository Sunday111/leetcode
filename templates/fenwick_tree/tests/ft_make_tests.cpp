#include <array>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <type_traits>

#include "fenwick_tree/ft_add.hpp"
#include "fenwick_tree/ft_make.hpp"
#include "fenwick_tree/ft_mul.hpp"
#include "fenwick_tree/ft_prefix.hpp"
#include "fenwick_tree/ft_range.hpp"
#include "fenwick_tree/ft_xor.hpp"
#include "gtest/gtest.h"
#include "integral_aliases.hpp"
#include "signed_integral_aliases.hpp"

TEST(FenwickTree, BuildsFromSourceWithoutChangingIt)
{
    int source[]{3, -2, 0, 5, -7};
    const auto original = std::to_array(source);
    std::array<int, 6> buffer{};
    buffer.fill(99);

    const auto tree =
        ft_make<int, unsigned, FenwickTreeAddTraits>(source, 5U, buffer.data());

    EXPECT_EQ(tree.x, buffer.data());
    EXPECT_EQ(tree.size, 5);
    EXPECT_EQ(buffer.front(), source[0]);
    EXPECT_EQ(buffer.back(), 99);
    EXPECT_EQ(std::to_array(source), original);
    EXPECT_EQ(ft_range(tree, 0, 5), -1);
    EXPECT_EQ(ft_range(tree, 1, 4), 3);
    EXPECT_EQ(ft_range(tree, 0, 1), 3);
    EXPECT_EQ(ft_range(tree, 4, 5), -7);
    EXPECT_EQ(ft_range(tree, 2, 2), 0);
    EXPECT_EQ(ft_range(tree, 5, 5), 0);
}

TEST(FenwickTree, EmptySource)
{
    const std::array<int, 0> source{};
    std::array<int, 0> buffer{};
    const auto tree = ft_make<int, std::size_t, FenwickTreeAddTraits>(
        source.data(),
        source.size(),
        buffer.data());

    EXPECT_EQ(tree.x, buffer.data());
    EXPECT_EQ(tree.size, 0);
    EXPECT_EQ(ft_range(tree, 0, 0), 0);
    EXPECT_EQ(ft_prefix(tree, 0), 0);

    const auto product = ft_make<int, std::size_t, FenwickTreeMulTraits>(
        source.data(),
        source.size(),
        buffer.data());
    EXPECT_EQ(ft_range(product, 0, 0), 1);
    EXPECT_EQ(ft_prefix(product, 0), 1);
}

TEST(FenwickTree, BuildsWithSmallIndexAtMaximumSize)
{
    std::array<int, 255> source{};
    source.fill(1);
    std::array<int, 255> buffer{};
    const auto tree = ft_make<int, std::uint8_t, FenwickTreeAddTraits>(
        source.data(),
        std::uint8_t{255},
        buffer.data());

    static_assert(std::same_as<decltype(tree.size), std::uint8_t>);
    EXPECT_EQ(tree.size, 255);
    EXPECT_EQ(ft_prefix(tree, 0), 0);
    EXPECT_EQ(ft_prefix(tree, 128), 128);
    EXPECT_EQ(ft_prefix(tree, 255), 255);
    EXPECT_EQ(ft_range(tree, 128, 255), 127);
}

template <typename T>
class FenwickTreeMakeTypedTest : public ::testing::Test
{
};

using FenwickTreeMakeValueTypes =
    ::testing::Types<u8, u16, u32, u64, i8, i16, i32, i64>;
TYPED_TEST_SUITE(FenwickTreeMakeTypedTest, FenwickTreeMakeValueTypes);

TYPED_TEST(FenwickTreeMakeTypedTest, Operations)
{
    using T = TypeParam;
    SCOPED_TRACE(sizeof(T));
    SCOPED_TRACE(std::is_signed_v<T>);
    const auto verify = []<typename Traits>(
                            Traits,
                            const std::array<T, 4>& source,
                            const std::array<T, 4>& expected)
    {
        std::array<T, 4> buffer{};
        const auto original = source;
        const auto tree =
            ft_make<T, u8, Traits>(source.data(), 4, buffer.data());
        EXPECT_EQ(tree.x, buffer.data());
        EXPECT_EQ(tree.size, 4);
        EXPECT_EQ(buffer, expected);
        EXPECT_EQ(source, original);
    };
    verify(FenwickTreeAddTraits{}, {1, 2, 3, 4}, {1, 3, 3, 10});
    verify(FenwickTreeMulTraits{}, {1, 2, 3, 4}, {1, 2, 3, 24});
    verify(FenwickTreeXORTraits{}, {1, 2, 3, 4}, {1, 3, 3, 4});
    if constexpr (std::is_signed_v<T>)
    {
        verify(FenwickTreeAddTraits{}, {-3, 2, -1, 4}, {-3, -1, -1, 2});
        verify(FenwickTreeMulTraits{}, {-3, 2, -1, 4}, {-3, -6, -1, 24});
        verify(FenwickTreeXORTraits{}, {-3, 2, -1, 4}, {-3, -1, -1, 4});
    }
    else
    {
        verify(
            FenwickTreeAddTraits{},
            {std::numeric_limits<T>::max(), 1, 1, 1},
            {std::numeric_limits<T>::max(), 0, 1, 2});
    }
}
