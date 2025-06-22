#include "0218_the_skyline_problem.hpp"
#include "gtest/gtest.h"

TEST(t0218_the_skyline_problem, test_1)
{
    std::vector<std::vector<int>> buildings{{
        {2, 9, 10},
        {3, 7, 15},
        {5, 12, 12},
        {15, 20, 10},
        {19, 24, 8},
    }};

    std::vector<std::vector<int>> expected{
        {{2, 10}, {3, 15}, {7, 12}, {12, 0}, {15, 10}, {20, 8}, {24, 0}}};

    auto actual = Solution::getSkyline(buildings);
    ASSERT_EQ(expected, actual);
}
