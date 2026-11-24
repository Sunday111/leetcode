#include <array>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <limits>
#include <type_traits>
#include <vector>

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

TEST(FenwickTree, AllRangesMatchReferenceBeforeAndAfterUpdates)
{
    const auto check = []<typename Traits>(Traits, auto op, int identity)
    {
        for (std::size_t size = 0; size <= 9; ++size)
        {
            SCOPED_TRACE(size);
            std::vector<int> source(size);
            for (std::size_t i = 0; i < size; ++i)
            {
                source.at(i) = i % 2 == 0 ? 2 : -1;
            }
            const auto original = source;
            auto reference = source;
            std::vector<int> buffer(size, 99);
            const auto tree = ft_make<int, std::size_t, Traits>(
                source.data(),
                source.size(),
                buffer.data());
            EXPECT_EQ(tree.size, size);

            const auto check_ranges = [&]
            {
                int prefix = identity;
                EXPECT_EQ(ft_prefix(tree, 0), prefix);
                for (std::size_t i = 0; i < size; ++i)
                {
                    EXPECT_EQ(ft_at(tree, i), reference.at(i));
                    prefix = op(prefix, reference.at(i));
                    EXPECT_EQ(ft_prefix(tree, i + 1), prefix);
                }
                for (std::size_t begin = 0; begin <= size; ++begin)
                {
                    int expected = identity;
                    for (std::size_t end = begin; end <= size; ++end)
                    {
                        if (end > begin)
                        {
                            expected = op(expected, reference.at(end - 1));
                        }
                        EXPECT_EQ(ft_range(tree, begin, end), expected)
                            << "range [" << begin << ", " << end << ')';
                    }
                }
            };

            check_ranges();
            for (int pass = 0; pass != 3; ++pass)
            {
                for (std::size_t i = 0; i < size; ++i)
                {
                    reference.at(i) = pass == 1 ? -2 : 3;
                    ft_update(tree, i, reference.at(i));
                    check_ranges();
                }
            }
            EXPECT_EQ(source, original);
        }
    };

    {
        SCOPED_TRACE("addition");
        check(FenwickTreeAddTraits{}, std::plus{}, 0);
    }
    {
        SCOPED_TRACE("xor");
        check(FenwickTreeXORTraits{}, std::bit_xor{}, 0);
    }
    {
        SCOPED_TRACE("multiplication");
        check(FenwickTreeMulTraits{}, std::multiplies{}, 1);
    }
}

template <typename T>
class FenwickTreeRangeTypedTest : public ::testing::Test
{
};

using FenwickTreeRangeValueTypes =
    ::testing::Types<u8, u16, u32, u64, i8, i16, i32, i64>;
TYPED_TEST_SUITE(FenwickTreeRangeTypedTest, FenwickTreeRangeValueTypes);

TYPED_TEST(FenwickTreeRangeTypedTest, Operations)
{
    using T = TypeParam;
    using Wide = std::conditional_t<std::is_signed_v<T>, i64, u64>;
    const auto verify = []<typename Traits>(
                            Traits,
                            const std::array<T, 4>& source,
                            auto op,
                            Wide identity)
    {
        std::array<T, 4> buffer{};
        const auto tree =
            ft_make<T, u8, Traits>(source.data(), 4, buffer.data());
        for (u8 begin = 0; begin != 5; ++begin)
        {
            Wide expected = identity;
            for (u8 end = begin; end != 5; ++end)
            {
                if (end != begin)
                {
                    expected = op(
                        expected,
                        static_cast<Wide>(source.at(static_cast<u8>(end - 1))));
                }
                EXPECT_EQ(ft_range(tree, begin, end), static_cast<T>(expected));
            }
        }
    };
    verify(FenwickTreeAddTraits{}, {1, 2, 3, 4}, std::plus{}, 0);
    verify(FenwickTreeMulTraits{}, {1, 2, 3, 4}, std::multiplies{}, 1);
    verify(FenwickTreeXORTraits{}, {1, 2, 3, 4}, std::bit_xor{}, 0);
    if constexpr (std::is_signed_v<T>)
    {
        verify(FenwickTreeAddTraits{}, {-3, 2, -1, 4}, std::plus{}, 0);
        verify(FenwickTreeMulTraits{}, {-3, 2, -1, 4}, std::multiplies{}, 1);
        verify(FenwickTreeXORTraits{}, {-3, 2, -1, 4}, std::bit_xor{}, 0);
    }
    else
    {
        verify(
            FenwickTreeAddTraits{},
            {std::numeric_limits<T>::max(), 1, 1, 1},
            std::plus{},
            0);
    }
}
