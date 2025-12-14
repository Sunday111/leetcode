#include "0053_maximum_subarray.hpp"
#include "gtest/gtest.h"

TEST(t0053_maximum_subarray, test_1)
{
    const std::vector nums{-2, 1, -3, 4, -1, 2, 1, -5, 4};
    ASSERT_EQ(Solution{}.maxSubArray(nums), 6);
}

TEST(t0053_maximum_subarray, test_2)
{
    const std::vector nums{1};
    ASSERT_EQ(Solution{}.maxSubArray(nums), 1);
}

TEST(t0053_maximum_subarray, test_3)
{
    const std::vector nums{5, 4, -1, 7, 8};
    ASSERT_EQ(Solution{}.maxSubArray(nums), 23);
}
