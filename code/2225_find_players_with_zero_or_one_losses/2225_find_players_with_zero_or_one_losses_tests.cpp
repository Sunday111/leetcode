#include "2225_find_players_with_zero_or_one_losses.hpp"
#include "gtest/gtest.h"

TEST(t2225_find_players_with_zero_or_one_losses, test_1)
{
    std::vector<std::vector<int>> input{
        {1, 3},
        {2, 3},
        {3, 6},
        {5, 6},
        {5, 7},
        {4, 5},
        {4, 8},
        {4, 9},
        {10, 4},
        {10, 9},
    };

    std::vector<std::vector<int>> expected{
        {1, 2, 10},
        {4, 5, 7, 8},
    };

    Solution s{};
    ASSERT_EQ(s.findWinners(input), expected);
}

TEST(t2225_find_players_with_zero_or_one_losses, test_2)
{
    std::vector<std::vector<int>> input{
        {2, 3},
        {1, 3},
        {5, 4},
        {6, 4},
    };

    std::vector<std::vector<int>> expected{
        {1, 2, 5, 6},
        {},
    };

    Solution s{};
    ASSERT_EQ(s.findWinners(input), expected);
}
