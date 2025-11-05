#include "3321_find_xsum_of_all_klong_subarrays_ii.hpp"
#include "gtest/gtest.h"

TEST(t3321_find_xsum_of_all_klong_subarrays_ii, test_1)
{
    std::vector<int> nums{1, 1, 2, 2, 3, 4, 2, 3};
    u32 k = 6;
    u32 x = 2;
    std::vector<long long> expected{6, 10, 12};
    ASSERT_EQ(Solution{}.findXSum(nums, k, x), expected);
}
