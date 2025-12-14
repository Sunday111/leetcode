#include "0070_climbing_stairs.hpp"
#include "gtest/gtest.h"

TEST(t0070_climbing_stairs, test_1)
{
    ASSERT_EQ(Solution{}.climbStairs(1), 1);
}
TEST(t0070_climbing_stairs, test_2)
{
    ASSERT_EQ(Solution{}.climbStairs(2), 2);
}
TEST(t0070_climbing_stairs, test_3)
{
    ASSERT_EQ(Solution{}.climbStairs(3), 3);
}
TEST(t0070_climbing_stairs, test_4)
{
    ASSERT_EQ(Solution{}.climbStairs(45), 1836311903);
}
