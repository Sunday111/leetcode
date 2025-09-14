#include "0966_vowel_spellcheck.hpp"
#include "gtest/gtest.h"

TEST(t0966_vowel_spellcheck, test_1)
{
    std::vector<std::string> worlist = {"KiTe", "kite", "hare", "Hare"};
    std::vector<std::string> queries = {
        "kite",
        "Kite",
        "KiTe",
        "Hare",
        "HARE",
        "Hear",
        "hear",
        "keti",
        "keet",
        "keto",
    };
    std::vector<std::string> expected{
        "kite",
        "KiTe",
        "KiTe",
        "Hare",
        "hare",
        "",
        "",
        "KiTe",
        "",
        "KiTe",
    };
    ASSERT_EQ(Solution{}.spellchecker(worlist, queries), expected);
}
