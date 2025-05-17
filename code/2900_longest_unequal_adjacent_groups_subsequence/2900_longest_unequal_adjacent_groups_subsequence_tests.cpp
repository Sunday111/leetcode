#include "2900_longest_unequal_adjacent_groups_subsequence.hpp"
#include "gtest/gtest.h"

TEST(t2900_longest_unequal_adjacent_groups_subsequence, test_1)
{
    std::vector<std::string> words{
        "d",
        "g",
    };

    std::vector groups{0, 1};
    std::vector<std::string> expected{"d", "g"};

    auto actual = Solution{}.getLongestSubsequence(words, groups);
    ASSERT_EQ(actual, expected);
}
