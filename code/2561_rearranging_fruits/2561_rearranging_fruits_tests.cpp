#include "2561_rearranging_fruits.hpp"
#include "gtest/gtest.h"

TEST(t2561_rearranging_fruits, test_1)
{
    std::vector nums1{4, 2, 2, 2};
    std::vector nums2{1, 4, 1, 2};
    ASSERT_EQ(Solution{}.minCost(nums1, nums2), 1);
}
