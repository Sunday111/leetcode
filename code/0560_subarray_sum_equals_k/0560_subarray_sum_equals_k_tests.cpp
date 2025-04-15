#include "0560_subarray_sum_equals_k.hpp"
#include "gtest/gtest.h"

TEST(t0560_subarray_sum_equals_k, test_1)
{
    Solution s{};
    std::vector input = {1, 1, 1};
    ASSERT_EQ(s.subarraySum(input, 2), 2);
}

TEST(t0560_subarray_sum_equals_k, test_2)
{
    Solution s{};
    std::vector input = {1, 2, 3};
    ASSERT_EQ(s.subarraySum(input, 3), 2);
}
