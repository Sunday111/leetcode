#include "3823_reverse_letters_then_special_characters_in_a_string.hpp"
#include "gtest/gtest.h"

TEST(t3823_reverse_letters_then_special_characters_in_a_string, test_1)
{
    std::string orig = ")ebc#da@f(";
    std::string expected = "(fad@cb#e)";
    ASSERT_EQ(Solution{}.reverseByType(orig), expected);
}

TEST(t3823_reverse_letters_then_special_characters_in_a_string, test_2)
{
    std::string orig = "!@#$%^&*()";
    std::string expected = ")(*&^%$#@!";
    ASSERT_EQ(Solution{}.reverseByType(orig), expected);
}
