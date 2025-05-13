#include "0022_generate_parentheses.hpp"
#include "gtest/gtest.h"
#include "test_utility.hpp"

TEST(t0022_generate_parentheses, test_1)
{
    constexpr int n = 3;
    std::vector<std::string> expected{
        "((()))",
        "(()())",
        "(())()",
        "()(())",
        "()()()",
    };

    auto actual = Solution{}.generateParenthesis(n);
    ASSERT_EQ(sorted(expected), sorted(actual));
}

TEST(t0022_generate_parentheses, test_2)
{
    constexpr int n = 1;
    std::vector<std::string> expected{
        "()",
    };

    auto actual = Solution{}.generateParenthesis(n);
    ASSERT_EQ(sorted(expected), sorted(actual));
}

TEST(t0022_generate_parentheses, test_3)
{
    constexpr int n = 5;
    std::vector<std::string> expected{
        "()()()()()", "()()()(())", "()()(())()", "()()(()())", "()()((()))",
        "()(())()()", "()(())(())", "()(()())()", "()(()()())", "()(()(()))",
        "()((()))()", "()((())())", "()((()()))", "()(((())))", "(())()()()",
        "(())()(())", "(())(())()", "(())(()())", "(())((()))", "(()())()()",
        "(()())(())", "(()()())()", "(()()()())", "(()()(()))", "(()(()))()",
        "(()(())())", "(()(()()))", "(()((())))", "((()))()()", "((()))(())",
        "((())())()", "((())()())", "((())(()))", "((()()))()", "((()())())",
        "((()()()))", "((()(())))", "(((())))()", "(((()))())", "(((())()))",
        "(((()())))", "((((()))))"};

    auto actual = Solution{}.generateParenthesis(n);
    ASSERT_EQ(sorted(expected), sorted(actual));
}
