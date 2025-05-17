#include "2901_longest_unequal_adjacent_groups_subsequence_2.hpp"
#include "gtest/gtest.h"

// TEST(t2901_longest_unequal_adjacent_groups_subsequence_2, test_1)
// {
//     std::vector<std::string> words{"bab", "dab", "cab"};

//     std::vector groups{1, 2, 2};
//     std::vector<std::string> expected{"bab", "cab"};

//     auto actual = Solution{}.getWordsInLongestSubsequence(words, groups);
//     ASSERT_EQ(actual, expected);
// }

TEST(t2901_longest_unequal_adjacent_groups_subsequence_2, test_2)
{
    std::vector<std::string> words{"a", "b", "c", "d"};

    std::vector groups{1, 2, 3, 4};
    std::vector<std::string> expected{"a", "b", "c", "d"};

    auto actual = Solution{}.getWordsInLongestSubsequence(words, groups);
    ASSERT_EQ(actual, expected);
}

TEST(t2901_longest_unequal_adjacent_groups_subsequence_2, test_3)
{
    std::vector<std::string> words{"bdb", "aaa", "ada"};

    std::vector groups{2, 1, 3};
    std::vector<std::string> expected{"aaa", "ada"};

    auto actual = Solution{}.getWordsInLongestSubsequence(words, groups);
    ASSERT_EQ(actual, expected);
}
