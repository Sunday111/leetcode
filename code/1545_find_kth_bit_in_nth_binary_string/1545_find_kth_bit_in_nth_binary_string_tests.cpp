
#include "1545_find_kth_bit_in_nth_binary_string.hpp"
#include "gtest/gtest.h"

TEST(t1545_find_kth_bit_in_nth_binary_string, test_1)
{
    ASSERT_EQ(Solution::findKthBit(3, 1), '0');
    ASSERT_EQ(Solution::findKthBit(4, 11), '1');
    ASSERT_EQ(Solution::findKthBit(4, 12), '0');
    ASSERT_EQ(Solution::findKthBit(3, 5), '0');
    ASSERT_EQ(Solution::findKthBit(3, 2), '1');
    ASSERT_EQ(Solution::findKthBit(20, 243002), '1');
    ASSERT_EQ(Solution::findKthBit(20, 189470), '0');
    ASSERT_EQ(Solution::findKthBit(17, 98304), '0');
    ASSERT_EQ(Solution::findKthBit(20, 426580), '1');
    ASSERT_EQ(Solution::findKthBit(20, 1048575), '1');
    ASSERT_EQ(Solution::findKthBit(20, 32944), '0');
}
