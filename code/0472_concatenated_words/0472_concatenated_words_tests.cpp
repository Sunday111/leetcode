#include "0472_concatenated_words.hpp"
#include "gtest/gtest.h"

TEST(t0472_concatenated_words, test_1)
{
    std::vector<std::string> words{
        "cat",
        "cats",
        "catsdogcats",
        "dog",
        "dogcatsdog",
        "hippopotamuses",
        "rat",
        "ratcatdogcat",
    };
    std::vector<std::string> expect{
        "catsdogcats",
        "dogcatsdog",
        "ratcatdogcat",
    };
    auto actual = Solution{}.findAllConcatenatedWordsInADict(words);
    std::ranges::sort(expect);
    std::ranges::sort(actual);
    ASSERT_EQ(actual, expect);
}
