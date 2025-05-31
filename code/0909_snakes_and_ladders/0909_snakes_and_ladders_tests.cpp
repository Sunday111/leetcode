#include "0909_snakes_and_ladders.hpp"
#include "gtest/gtest.h"

TEST(t0909_snakes_and_ladders, test_1)
{
    std::vector<std::vector<int>> board{
        {-1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1},
        {-1, 35, -1, -1, 13, -1},
        {-1, -1, -1, -1, -1, -1},
        {-1, 15, -1, -1, -1, -1},
    };
    ASSERT_EQ(Solution{}.snakesAndLadders(board), 4);
}

TEST(t0909_snakes_and_ladders, test_2)
{
    std::vector<std::vector<int>> board{
        {-1, -1, -1},
        {-1, 9, 8},
        {-1, 8, 9},
    };
    ASSERT_EQ(Solution{}.snakesAndLadders(board), 1);
}
