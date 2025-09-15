#include "2563_count_the_number_of_fair_pairs.hpp"
#include "gtest/gtest.h"

TEST(t2563_count_the_number_of_fair_pairs, test_1)
{
    std::vector<i32> nums{0, 1, 7, 4, 4, 5};
    ASSERT_EQ(Solution{}.countFairPairs(nums, 3, 6), 6);
}
