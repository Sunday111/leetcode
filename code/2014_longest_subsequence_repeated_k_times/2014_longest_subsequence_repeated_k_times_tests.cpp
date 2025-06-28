#include "2014_longest_subsequence_repeated_k_times.hpp"
#include "gtest/gtest.h"

TEST(t2014_longest_subsequence_repeated_k_times, test_1)
{
    std::string s = "letsleetcode";
    ASSERT_EQ(Solution{}.longestSubsequenceRepeatedK(s, 2), "let");
}

TEST(t2014_longest_subsequence_repeated_k_times, test_2)
{
    std::string s = "bb";
    ASSERT_EQ(Solution{}.longestSubsequenceRepeatedK(s, 2), "b");
}

TEST(t2014_longest_subsequence_repeated_k_times, test_3)
{
    std::string s = "ab";
    ASSERT_EQ(Solution{}.longestSubsequenceRepeatedK(s, 2), "");
}

TEST(t2014_longest_subsequence_repeated_k_times, test_4)
{
    std::string s = "nhsbbeonhsbbeonhsbbeo";
    ASSERT_EQ(Solution{}.longestSubsequenceRepeatedK(s, 3), "nhsbbeo");
}

TEST(t2014_longest_subsequence_repeated_k_times, test_5)
{
    std::string s = "gbjbjigjbji";
    ASSERT_EQ(Solution{}.longestSubsequenceRepeatedK(s, 2), "gjbji");
}
