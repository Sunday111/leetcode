#include "2616_minimize_the_maximum_difference_of_pairs.hpp"
#include "gtest/gtest.h"

TEST(t2616_minimize_the_maximum_difference_of_pairs, test_1)
{
    std::vector nums{10, 1, 2, 7, 1, 3};
    uint32_t p = 2;
    ASSERT_EQ(Solution::minimizeMax(nums, p), 1);
}

TEST(t2616_minimize_the_maximum_difference_of_pairs, test_2)
{
    std::vector nums{4, 2, 1, 2};
    uint32_t p = 1;
    ASSERT_EQ(Solution::minimizeMax(nums, p), 0);
}

TEST(t2616_minimize_the_maximum_difference_of_pairs, test_3)
{
    std::vector
        nums{1, 2000, 2001, 2002, 3002, 4000, 4002, 5000, 6000, 6003, 10000};
    uint32_t p = 4;
    ASSERT_EQ(Solution::minimizeMax(nums, p), 998);
}

TEST(t2616_minimize_the_maximum_difference_of_pairs, test_4)
{
    std::vector nums{3, 4, 2, 3, 2, 1, 2};
    uint32_t p = 3;
    ASSERT_EQ(Solution::minimizeMax(nums, p), 1);
}
