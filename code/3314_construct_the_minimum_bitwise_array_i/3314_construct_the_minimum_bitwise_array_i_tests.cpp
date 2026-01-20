#include "3314_construct_the_minimum_bitwise_array_i.hpp"
#include "gtest/gtest.h"

TEST(t3314_construct_the_minimum_bitwise_array_i, test_1)
{
    std::vector nums{2,3,5,7}, expected{-1,1,4,3};
    auto actual = Solution{}.minBitwiseArray(nums);
    ASSERT_EQ(actual, expected);
}


TEST(t3314_construct_the_minimum_bitwise_array_i, test_2)
{
    std::vector nums{11,13,31}, expected{9,12,15};
    auto actual = Solution{}.minBitwiseArray(nums);
    ASSERT_EQ(actual, expected);
}
