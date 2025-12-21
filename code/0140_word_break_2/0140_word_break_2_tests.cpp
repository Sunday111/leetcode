#include <algorithm>

#include "0140_word_break_2.hpp"
#include "gtest/gtest.h"

TEST(t0140_word_break_2, test_1)
{
    std::string s = "catsanddog";
    std::vector<std::string> words = {"cat", "cats", "and", "sand", "dog"};
    std::vector<std::string> expect = {"cats and dog", "cat sand dog"};
    std::ranges::sort(words);
    std::ranges::sort(expect);
    ASSERT_EQ(Solution{}.wordBreak(s, words), expect);
}

TEST(t0140_word_break_2, test_2)
{
    std::string s = "pineapplepenapple";
    std::vector<std::string> words =
        {"apple", "pen", "applepen", "pine", "pineapple"};
    std::vector<std::string> expect = {
        "pine apple pen apple",
        "pineapple pen apple",
        "pine applepen apple"};
    std::ranges::sort(words);
    std::ranges::sort(expect);
    ASSERT_EQ(Solution{}.wordBreak(s, words), expect);
}
