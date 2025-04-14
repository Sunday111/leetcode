#include <algorithm>
#include <vector>

#include "0301_remove_invalid_parentheses.hpp"
#include "gtest/gtest.h"

TEST(t0301_remove_invalid_parentheses, test_1)
{
    Solution s{};
    std::vector<std::string> expected{"(())()", "()()()"};
    std::ranges::sort(expected);

    auto result = s.removeInvalidParentheses("()())()");
    std::ranges::sort(result);

    ASSERT_EQ(result, expected);
}

TEST(t0301_remove_invalid_parentheses, test_2)
{
    Solution s{};
    std::vector<std::string> expected{""};
    ASSERT_EQ(s.removeInvalidParentheses("))(("), expected);
}

TEST(t0301_remove_invalid_parentheses, test_3)
{
    Solution s{};
    std::vector<std::string> expected{"()"};
    ASSERT_EQ(s.removeInvalidParentheses(")()("), expected);
}

TEST(t0301_remove_invalid_parentheses, test_4)
{
    Solution s{};
    std::vector<std::string> expected{"((aaaaa))"};
    std::ranges::sort(expected);

    auto result = s.removeInvalidParentheses("((((((((((((((((((aaaaa))");
    std::ranges::sort(result);

    ASSERT_EQ(result, expected);
}

TEST(t0301_remove_invalid_parentheses, test_5)
{
    Solution s{};
    std::vector<std::string> expected{"k()", "(k)"};
    std::ranges::sort(expected);

    auto result = s.removeInvalidParentheses("(((k()((");
    std::ranges::sort(result);

    ASSERT_EQ(result, expected);
}
