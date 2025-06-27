#include "2014_longest_subsequence_repeated_k_times.hpp"
#include "gtest/gtest.h"

TEST(t2014_longest_subsequence_repeated_k_times, test_1)
{
    ASSERT_EQ(Solution{}.longestSubsequenceRepeatedK("letsleetcode", 2), "let");
}

TEST(t2014_longest_subsequence_repeated_k_times, test_2)
{
    ASSERT_EQ(Solution{}.longestSubsequenceRepeatedK("bb", 2), "b");
}

TEST(t2014_longest_subsequence_repeated_k_times, test_3)
{
    ASSERT_EQ(Solution{}.longestSubsequenceRepeatedK("ab", 2), "");
}

TEST(t2014_longest_subsequence_repeated_k_times, test_4)
{
    ASSERT_EQ(
        Solution{}.longestSubsequenceRepeatedK("nhsbbeonhsbbeonhsbbeo", 3),
        "nhsbbeo");
}

TEST(t2014_longest_subsequence_repeated_k_times, test_5)
{
    ASSERT_EQ(
        Solution{}.longestSubsequenceRepeatedK("gbjbjigjbji", 2),
        "gjbji");
}
