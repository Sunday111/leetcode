#include "1590_make_sum_divisible_by_p.hpp"
#include "gtest/gtest.h"

// TEST(t1590_make_sum_divisible_by_p, test_1)
// {
//     std::vector nums{3, 1, 4, 2};
//     ASSERT_EQ(Solution{}.minSubarray(nums, 6), 1);
// }

TEST(t1590_make_sum_divisible_by_p, test_2)
{
    std::vector<int> nums;
    nums.resize(100'002, 1);
    ASSERT_EQ(Solution{}.minSubarray(nums, 123123), 1);
}
