#include "3838_weighted_word_mapping.hpp"
#include "gtest/gtest.h"

TEST(t3838_weighted_word_mapping, test_1)
{
    std::vector<std::string> words{"abcd", "def", "xyz"};
    std::vector weights{5, 3, 12, 14, 1, 2, 3, 2, 10, 6, 6, 9, 7,
                        8, 7, 10, 8,  9, 6, 9, 9, 8,  3, 7, 7, 2};
    std::string expected = "rij";
    ASSERT_EQ(Solution{}.mapWordWeights(words, weights), expected);
}

TEST(t3838_weighted_word_mapping, test_2)
{
    std::vector<std::string> words{"a", "b", "c"};
    std::vector weights{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    std::string expected = "yyy";
    ASSERT_EQ(Solution{}.mapWordWeights(words, weights), expected);
}

TEST(t3838_weighted_word_mapping, test_3)
{
    std::vector<std::string> words{"abcd"};
    std::vector weights{7, 5, 3,  4, 3, 5, 4, 9, 4, 2, 2, 7, 10,
                        2, 5, 10, 6, 1, 2, 2, 4, 1, 3, 4, 4, 5};
    std::string expected = "g";
    ASSERT_EQ(Solution{}.mapWordWeights(words, weights), expected);
}
