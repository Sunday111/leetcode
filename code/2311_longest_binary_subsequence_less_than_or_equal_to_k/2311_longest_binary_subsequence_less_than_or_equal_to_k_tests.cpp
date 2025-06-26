#include "2311_longest_binary_subsequence_less_than_or_equal_to_k.hpp"
#include "gtest/gtest.h"

TEST(t2311_longest_binary_subsequence_less_than_or_equal_to_k, test_1)
{
    ASSERT_EQ(Solution{}.longestSubsequence("1001010", 5), 5);
}
