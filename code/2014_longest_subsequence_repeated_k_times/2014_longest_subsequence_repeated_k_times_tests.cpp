#include "2014_longest_subsequence_repeated_k_times.hpp"
#include "gtest/gtest.h"

// TEST(t2014_longest_subsequence_repeated_k_times, test_1)
// {
//     using S = Solution;
//     std::string s1 = "letsleetcode";
//     ASSERT_EQ(S{}.longestSubsequenceRepeatedK(s1, 2), "let");
//     std::string s2 = "bb";
//     ASSERT_EQ(S{}.longestSubsequenceRepeatedK(s2, 2), "b");
//     std::string s3 = "ab";
//     ASSERT_EQ(S{}.longestSubsequenceRepeatedK(s3, 2), "");
//     std::string s4 = "nhsbbeonhsbbeonhsbbeo";
//     ASSERT_EQ(S{}.longestSubsequenceRepeatedK(s4, 3), "nhsbbeo");
//     std::string s5 = "gbjbjigjbji";
//     ASSERT_EQ(S{}.longestSubsequenceRepeatedK(s5, 2), "gjbji");
// }
// TEST(t2014_longest_subsequence_repeated_k_times, test_2)
// {
//     using S = Solution2;
//     std::string s1 = "letsleetcode";
//     ASSERT_EQ(S{}.longestSubsequenceRepeatedK(s1, 2), "let");
//     std::string s2 = "bb";
//     ASSERT_EQ(S{}.longestSubsequenceRepeatedK(s2, 2), "b");
//     std::string s3 = "ab";
//     ASSERT_EQ(S{}.longestSubsequenceRepeatedK(s3, 2), "");
//     std::string s4 = "nhsbbeonhsbbeonhsbbeo";
//     ASSERT_EQ(S{}.longestSubsequenceRepeatedK(s4, 3), "nhsbbeo");
//     std::string s5 = "gbjbjigjbji";
//     ASSERT_EQ(S{}.longestSubsequenceRepeatedK(s5, 2), "gjbji");
// }
TEST(t2014_longest_subsequence_repeated_k_times, test_3)
{
    using S = Solution3;
    std::string s1 = "letsleetcode";
    ASSERT_EQ(S{}.longestSubsequenceRepeatedK(s1, 2), "let");
    std::string s2 = "bb";
    ASSERT_EQ(S{}.longestSubsequenceRepeatedK(s2, 2), "b");
    std::string s3 = "ab";
    ASSERT_EQ(S{}.longestSubsequenceRepeatedK(s3, 2), "");
    std::string s4 = "nhsbbeonhsbbeonhsbbeo";
    ASSERT_EQ(S{}.longestSubsequenceRepeatedK(s4, 3), "nhsbbeo");
    std::string s5 = "gbjbjigjbji";
    ASSERT_EQ(S{}.longestSubsequenceRepeatedK(s5, 2), "gjbji");
}
