#include <array>

#include "fenwick_tree/ft_add.hpp"
#include "fenwick_tree/ft_make.hpp"
#include "fenwick_tree/ft_mul.hpp"
#include "fenwick_tree/ft_prefix.hpp"
#include "fenwick_tree/ft_update.hpp"
#include "fenwick_tree/ft_xor.hpp"
#include "gtest/gtest.h"
#include "integral_aliases.hpp"
#include "signed_integral_aliases.hpp"

TEST(FenwickTree, PrefixExcludesEnd)
{
    const int source[]{3, -2, 0, 5, -7};
    int buffer[5]{};
    const auto tree =
        ft_make<int, unsigned, FenwickTreeAddTraits>(source, 5U, buffer);

    EXPECT_EQ(ft_prefix(tree, 0), 0);
    EXPECT_EQ(ft_prefix(tree, 1), 3);
    EXPECT_EQ(ft_prefix(tree, 2), 1);
    EXPECT_EQ(ft_prefix(tree, 3), 1);
    EXPECT_EQ(ft_prefix(tree, 4), 6);
    EXPECT_EQ(ft_prefix(tree, 5), -1);

    ft_update(tree, 1, 4);
    EXPECT_EQ(ft_prefix(tree, 1), 3);
    EXPECT_EQ(ft_prefix(tree, 2), 7);
    EXPECT_EQ(ft_prefix(tree, 5), 5);
}

template <typename T>
class FenwickTreePrefixTypedTest : public ::testing::Test
{
};

using FenwickTreePrefixValueTypes =
    ::testing::Types<u8, u16, u32, u64, i8, i16, i32, i64>;
TYPED_TEST_SUITE(FenwickTreePrefixTypedTest, FenwickTreePrefixValueTypes);

TYPED_TEST(FenwickTreePrefixTypedTest, Operations)
{
    using T = TypeParam;
    const std::array<T, 4> source{1, 2, 3, 4};
    const auto verify =
        [&]<typename Traits>(Traits, const std::array<T, 5>& expected)
    {
        std::array<T, 4> buffer{};
        const auto tree =
            ft_make<T, u8, Traits>(source.data(), 4, buffer.data());
        for (u8 end = 0; end != 5; ++end)
        {
            EXPECT_EQ(ft_prefix(tree, end), expected.at(end));
        }
    };
    verify(FenwickTreeAddTraits{}, {0, 1, 3, 6, 10});
    verify(FenwickTreeMulTraits{}, {1, 1, 2, 6, 24});
    verify(FenwickTreeXORTraits{}, {0, 1, 3, 0, 4});
}
