#include "0680_valid_palindrome.hpp"
#include "gtest/gtest.h"

TEST(s0680_valid_palindrome, test_1)
{
    Solution s{};

    ASSERT_TRUE(s.validPalindrome("cupuuffuupucu"));
}

TEST(s0680_valid_palindrome, test_2)
{
    Solution s{};

    ASSERT_TRUE(s.validPalindrome("deeee"));
}
