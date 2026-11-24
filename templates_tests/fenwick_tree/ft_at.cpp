#include <array>
#include <limits>
#include <type_traits>

#include "fenwick_tree/ft_add.hpp"
#include "fenwick_tree/ft_at.hpp"
#include "fenwick_tree/ft_make.hpp"
#include "fenwick_tree/ft_mul.hpp"
#include "fenwick_tree/ft_update.hpp"
#include "fenwick_tree/ft_xor.hpp"
#include "gtest/gtest.h"
#include "integral_aliases.hpp"
#include "signed_integral_aliases.hpp"

TEST(FenwickTree, AtReturnsElementValue)
{
    const int source[]{3, -2, 0, 5, -7};
    int buffer[5]{};
    const auto tree =
        ft_make<int, unsigned, FenwickTreeAddTraits>(source, 5U, buffer);

    for (decltype(tree.size) i = 0; i < tree.size; ++i)
    {
        EXPECT_EQ(ft_at(tree, i), source[i]);
    }

    ft_update(tree, 0, 8);
    ft_update(tree, 4, 2);
    EXPECT_EQ(ft_at(tree, 0), 8);
    EXPECT_EQ(ft_at(tree, 1), -2);
    EXPECT_EQ(ft_at(tree, 4), 2);
}

template <typename T>
class FenwickTreeAtTypedTest : public ::testing::Test
{
};

using FenwickTreeAtValueTypes =
    ::testing::Types<u8, u16, u32, u64, i8, i16, i32, i64>;
TYPED_TEST_SUITE(FenwickTreeAtTypedTest, FenwickTreeAtValueTypes);

TYPED_TEST(FenwickTreeAtTypedTest, Operations)
{
    using T = TypeParam;
    const auto verify =
        []<typename Traits>(Traits, const std::array<T, 4>& source)
    {
        std::array<T, 4> buffer{};
        const auto tree =
            ft_make<T, u8, Traits>(source.data(), 4, buffer.data());
        for (u8 i = 0; i != 4; ++i)
        {
            EXPECT_EQ(ft_at(tree, i), source.at(i));
        }
    };
    if constexpr (std::is_signed_v<T>)
    {
        verify(
            FenwickTreeAddTraits{},
            {std::numeric_limits<T>::max(), -1, -1, -1});
    }
    else
    {
        verify(
            FenwickTreeAddTraits{},
            {std::numeric_limits<T>::max(), 1, 1, 1});
    }
    verify(FenwickTreeMulTraits{}, {std::numeric_limits<T>::max(), 1, 1, 1});
    verify(FenwickTreeXORTraits{}, {std::numeric_limits<T>::max(), 1, 1, 1});
    if constexpr (std::is_signed_v<T>)
    {
        verify(
            FenwickTreeAddTraits{},
            {std::numeric_limits<T>::min(), 1, 1, 1});
        verify(
            FenwickTreeMulTraits{},
            {std::numeric_limits<T>::min(), 1, 1, 1});
        verify(
            FenwickTreeXORTraits{},
            {std::numeric_limits<T>::min(), 1, 1, 1});
    }
}
