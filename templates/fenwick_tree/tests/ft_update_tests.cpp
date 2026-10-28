#include <array>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <type_traits>

#include "fenwick_tree/ft_add.hpp"
#include "fenwick_tree/ft_at.hpp"
#include "fenwick_tree/ft_make.hpp"
#include "fenwick_tree/ft_mul.hpp"
#include "fenwick_tree/ft_prefix.hpp"
#include "fenwick_tree/ft_range.hpp"
#include "fenwick_tree/ft_update.hpp"
#include "fenwick_tree/ft_xor.hpp"
#include "gtest/gtest.h"
#include "integral_aliases.hpp"
#include "signed_integral_aliases.hpp"

TEST(FenwickTree, ReplacesSingleElement)
{
    const std::array source{7};
    std::array<int, 1> buffer{};
    const auto tree = ft_make<int, std::size_t, FenwickTreeAddTraits>(
        source.data(),
        source.size(),
        buffer.data());

    for (int value : {0, -5, -5, 9})
    {
        ft_update(tree, 0, value);
        EXPECT_EQ(ft_range(tree, 0, 1), value);
        EXPECT_EQ(ft_at(tree, 0), value);
    }
    EXPECT_EQ(source.front(), 7);
}

TEST(FenwickTree, ReplacesIntegerProductWithNonMultiple)
{
    const std::array source{2, 3, 5};
    std::array<int, 3> buffer{};
    const auto tree = ft_make<int, std::size_t, FenwickTreeMulTraits>(
        source.data(),
        source.size(),
        buffer.data());

    ft_update(tree, 0, 3);
    EXPECT_EQ(ft_range(tree, 0, 3), 45);
    EXPECT_EQ(ft_range(tree, 0, 1), 3);
    EXPECT_EQ(ft_range(tree, 1, 3), 15);
}

TEST(FenwickTree, SupportsConstantEvaluation)
{
    constexpr auto result = []
    {
        const std::array source{1, 2, 3};
        std::array<int, 3> buffer{};
        const auto tree = ft_make<int, std::size_t, FenwickTreeAddTraits>(
            source.data(),
            source.size(),
            buffer.data());
        ft_update(tree, 1, 5);
        return std::array{
            ft_range(tree, 0, 3),
            ft_prefix(tree, 2),
            ft_at(tree, 1)};
    }();
    static_assert(result == std::array{9, 6, 5});
    EXPECT_EQ(result, (std::array{9, 6, 5}));
}

TEST(FenwickTree, UpdatesWithSmallIndexAtMaximumSize)
{
    std::array<int, 255> source{};
    source.fill(1);
    std::array<int, 255> buffer{};
    const auto tree = ft_make<int, std::uint8_t, FenwickTreeAddTraits>(
        source.data(),
        std::uint8_t{255},
        buffer.data());

    ft_update(tree, 254, 3);
    ft_update(tree, 0, -2);

    EXPECT_EQ(ft_at(tree, 254), 3);
    EXPECT_EQ(ft_at(tree, 0), -2);
    EXPECT_EQ(ft_prefix(tree, 255), 254);
    EXPECT_EQ(ft_range(tree, 1, 254), 253);
}

template <typename T>
class FenwickTreeUpdateTypedTest : public ::testing::Test
{
};

using FenwickTreeUpdateValueTypes =
    ::testing::Types<u8, u16, u32, u64, i8, i16, i32, i64>;
TYPED_TEST_SUITE(FenwickTreeUpdateTypedTest, FenwickTreeUpdateValueTypes);

TYPED_TEST(FenwickTreeUpdateTypedTest, Operations)
{
    using T = TypeParam;
    using Wide = std::conditional_t<std::is_signed_v<T>, i64, u64>;
    const auto verify = []<typename Traits>(Traits, auto op, Wide identity)
    {
        const std::array<T, 4> source{1, 2, 3, 4};
        auto reference = source;
        std::array<T, 4> buffer{};
        const auto tree =
            ft_make<T, u8, Traits>(source.data(), 4, buffer.data());
        std::array<T, 4> replacements{2, 3, 1, 1};
        if constexpr (std::is_signed_v<T>)
        {
            replacements = {-2, -3, -1, -1};
        }
        for (u8 i = 0; i != 4; ++i)
        {
            reference.at(i) = replacements.at(i);
            ft_update(tree, i, replacements.at(i));
            for (u8 begin = 0; begin != 5; ++begin)
            {
                Wide expected = identity;
                for (u8 end = begin; end != 5; ++end)
                {
                    if (end != begin)
                    {
                        expected =
                            op(expected,
                               static_cast<Wide>(
                                   reference.at(static_cast<u8>(end - 1))));
                    }
                    EXPECT_EQ(
                        ft_range(tree, begin, end),
                        static_cast<T>(expected));
                }
            }
        }
    };
    verify(FenwickTreeAddTraits{}, std::plus{}, 0);
    verify(FenwickTreeMulTraits{}, std::multiplies{}, 1);
    verify(FenwickTreeXORTraits{}, std::bit_xor{}, 0);
}

template <typename T>
class FenwickTreeUnsignedUpdateTypedTest : public ::testing::Test
{
};

using FenwickTreeUnsignedValueTypes = ::testing::Types<u8, u16, u32, u64>;
TYPED_TEST_SUITE(
    FenwickTreeUnsignedUpdateTypedTest,
    FenwickTreeUnsignedValueTypes);

TYPED_TEST(FenwickTreeUnsignedUpdateTypedTest, Wraparound)
{
    using T = TypeParam;
    const std::array<T, 3> source{std::numeric_limits<T>::max(), 2, 3};
    std::array<T, 3> buffer{};
    const auto tree =
        ft_make<T, u8, FenwickTreeAddTraits>(source.data(), 3, buffer.data());
    EXPECT_EQ(ft_range(tree, 0, 3), T{4});
    ft_update(tree, 0, T{1});
    EXPECT_EQ(ft_range(tree, 0, 3), T{6});
    ft_update(tree, 1, std::numeric_limits<T>::max());
    EXPECT_EQ(ft_range(tree, 0, 3), T{3});
    EXPECT_EQ(ft_at(tree, 0), T{1});
    EXPECT_EQ(ft_at(tree, 1), std::numeric_limits<T>::max());
    EXPECT_EQ(ft_at(tree, 2), T{3});
}
