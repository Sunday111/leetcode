#include "2163_minimum_difference_in_sums_after_removal_of_elements.hpp"
#include "gtest/gtest.h"

TEST(t2163_minimum_difference_in_sums_after_removal_of_elements, test_1)
{
    std::vector nums{3, 1, 2};
    ASSERT_EQ(all_branches::Solution{}.minimumDifference(nums), -1);
}
