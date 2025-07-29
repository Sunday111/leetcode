#include "2411_smallest_subarrays_with_maximum_bitwise_or.hpp"
#include "gtest/gtest.h"

TEST(t2411_smallest_subarrays_with_maximum_bitwise_or, test_0)
{
    std::vector<int> nums{0};
    std::vector<int> expected{1};
    ASSERT_EQ(Solution{}.smallestSubarrays(nums), expected);
}

TEST(t2411_smallest_subarrays_with_maximum_bitwise_or, test_1)
{
    std::vector<int> nums{1, 0, 2, 1, 3};
    std::vector<int> expected{3, 3, 2, 2, 1};
    ASSERT_EQ(Solution{}.smallestSubarrays(nums), expected);
}
