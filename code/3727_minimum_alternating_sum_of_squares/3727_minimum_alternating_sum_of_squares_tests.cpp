#include "3727_minimum_alternating_sum_of_squares.hpp"
#include "gtest/gtest.h"

TEST(t3727_minimum_alternating_sum_of_squares, test_1)
{
    std::vector nums{1, 2, 3};
    ASSERT_EQ(Solution{}.maxAlternatingSum(nums), 12);
}
TEST(t3727_minimum_alternating_sum_of_squares, test_2)
{
    std::vector nums{1, -1, 2, -2, 3, -3};
    ASSERT_EQ(Solution{}.maxAlternatingSum(nums), 16);
}
