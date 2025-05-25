#include <print>

#include "0289_game_of_life.hpp"
#include "gtest/gtest.h"

TEST(t0289_game_of_life, test_1)
{
    std::vector<std::vector<int>> board{
        {0, 1, 0},
        {0, 0, 1},
        {1, 1, 1},
        {0, 0, 0}};
    std::vector<std::vector<int>> expected{
        {0, 0, 0},
        {1, 0, 1},
        {0, 1, 1},
        {0, 1, 0},
    };

    Solution{}.gameOfLife(board);

    std::println("Expected:");
    for (auto& row : expected)
    {
        std::println("    {}", row);
    }

    std::println("Actual:");
    for (auto& row : board)
    {
        std::println("    {}", row);
    }
    ASSERT_EQ(expected, board);
}
