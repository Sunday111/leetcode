#include "3583_count_special_triplets.hpp"
#include "gtest/gtest.h"

TEST(t3583_count_special_triplets, test_1)
{
    std::vector<int> nums{6, 3, 6};
    ASSERT_EQ(Solution{}.specialTriplets(nums), 1);
}

TEST(t3583_count_special_triplets, test_2)
{
    std::vector<int> nums{0, 1, 0, 0};
    ASSERT_EQ(Solution{}.specialTriplets(nums), 1);
}
