#include "2273_find_resultant_array_after_removing_anagrams.hpp"
#include "gtest/gtest.h"

TEST(t2273_find_resultant_array_after_removing_anagrams, test_1)
{
    std::vector<std::string> words{
        "a",
        "b",
        "c",
        "d",
        "e",
    };
    const std::vector<std::string> expected{
        "a",
        "b",
        "c",
        "d",
        "e",
    };
    Solution s{};
    ASSERT_EQ(s.removeAnagrams(words), expected);
}

TEST(t2273_find_resultant_array_after_removing_anagrams, test_2)
{
    std::vector<std::string> words{"abba", "baba", "bbaa", "cd", "cd"};
    const std::vector<std::string> expected{"abba", "cd"};
    Solution s{};
    ASSERT_EQ(s.removeAnagrams(words), expected);
}
