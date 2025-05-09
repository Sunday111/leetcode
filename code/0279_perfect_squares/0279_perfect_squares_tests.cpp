#include "0279_perfect_squares.hpp"
#include "gtest/gtest.h"

TEST(t0279_perfect_squares, test_1)
{
    Solution s{};
    ASSERT_EQ(s.numSquares(12), 3);
}

TEST(t0279_perfect_squares, test_2)
{
    Solution s{};
    ASSERT_EQ(s.numSquares(13), 2);
}

TEST(t0279_perfect_squares, test_3)
{
    Solution s{};
    ASSERT_EQ(s.numSquares(1), 1);
}

TEST(t0279_perfect_squares, test_4)
{
    Solution s{};
    ASSERT_EQ(s.numSquares(7168), 4);
}

TEST(t0279_perfect_squares, test_5)
{
    Solution s{};
    ASSERT_EQ(s.numSquares(7217), 3);
}

template <typename To, typename From, size_t extent = std::dynamic_extent>
    requires(
        ((sizeof(From) % sizeof(To)) == 0) ||
        ((sizeof(To) % sizeof(From)) == 0))
inline constexpr auto spanCast(std::span<From, extent> from)
{
    if constexpr (extent == std::dynamic_extent)
    {
        assert(((sizeof(From) * from.size()) % sizeof(To) == 0));
        const size_t n = (sizeof(From) * from.size()) / sizeof(To);
        return std::span{reinterpret_cast<To*>(from.data()), n};  // NOLINT
    }
    else
    {
        static_assert(((sizeof(From) * extent) % sizeof(To) == 0));
        constexpr size_t n = (sizeof(From) * extent) / sizeof(To);
        return std::span<To, n>{
            reinterpret_cast<To*>(from.data()),  // NOLINT
            n};
    }
}
