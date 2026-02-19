#include "0761_special_binary_string.hpp"
#include "gtest/gtest.h"

TEST(t0761_special_binary_string, test_1)
{
    std::string orig = "11011000";
    std::string expected = "11100100";
    ASSERT_EQ(Solution{}.makeLargestSpecial(orig), expected);
}

TEST(t0761_special_binary_string, test_2)
{
    std::string orig = "10";
    std::string expected = "10";
    ASSERT_EQ(Solution{}.makeLargestSpecial(orig), expected);
}

TEST(t0761_special_binary_string, test_3)
{
    std::string orig = "110110100100";
    std::string expected = "111010010100";
    ASSERT_EQ(Solution{}.makeLargestSpecial(orig), expected);
}
