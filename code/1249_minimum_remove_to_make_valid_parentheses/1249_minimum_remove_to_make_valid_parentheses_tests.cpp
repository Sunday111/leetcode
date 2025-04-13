#include "1249_minimum_remove_to_make_valid_parentheses.hpp"
#include "gtest/gtest.h"

TEST(t1249_minimum_remove_to_make_valid_parentheses, test_1)
{
    Solution s{};
    ASSERT_EQ(s.minRemoveToMakeValid("lee(t(c)o)de)"), "lee(t(c)o)de");
}

TEST(t1249_minimum_remove_to_make_valid_parentheses, test_2)
{
    Solution s{};
    ASSERT_EQ(s.minRemoveToMakeValid("a)b(c)d"), "ab(c)d");
}

TEST(t1249_minimum_remove_to_make_valid_parentheses, test_3)
{
    Solution s{};
    ASSERT_EQ(s.minRemoveToMakeValid("))(("), "");
}

TEST(t1249_minimum_remove_to_make_valid_parentheses, test_4)
{
    Solution s{};
    ASSERT_EQ(s.minRemoveToMakeValid("(a(b(c)d)"), "a(b(c)d)");
}
