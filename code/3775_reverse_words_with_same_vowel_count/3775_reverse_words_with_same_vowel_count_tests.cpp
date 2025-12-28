#include "3775_reverse_words_with_same_vowel_count.hpp"
#include "gtest/gtest.h"

TEST(t3775_reverse_words_with_same_vowel_count, test_1)
{
    std::string in = "cat and mice";
    std::string expect = "cat dna mice";
    ASSERT_EQ(Solution{}.reverseWords(in), expect);
}
