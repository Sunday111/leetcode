#include "2099_find_subsequence_of_length_k_with_largest_sum.hpp"
#include "gtest/gtest.h"

TEST(t2099_find_subsequence_of_length_k_with_largest_sum, test_1)
{
    std::vector<int> nums{50, -75};
    std::vector<int> expected{50, -75};
    ASSERT_EQ(Solution{}.maxSubsequence(nums, 2), expected);
}
