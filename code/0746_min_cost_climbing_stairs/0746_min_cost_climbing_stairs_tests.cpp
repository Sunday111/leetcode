#include "0746_min_cost_climbing_stairs.hpp"
#include "gtest/gtest.h"

TEST(t0746_min_cost_climbing_stairs, test_1)
{
    std::vector cost{10, 15, 20};
    ASSERT_EQ(Solution{}.minCostClimbingStairs(cost), 15);
}

TEST(t0746_min_cost_climbing_stairs, test_2)
{
    std::vector cost{1, 100, 1, 1, 1, 100, 1, 1, 100, 1};
    ASSERT_EQ(Solution{}.minCostClimbingStairs(cost), 6);
}
