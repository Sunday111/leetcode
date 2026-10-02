#pragma once

#include "0022.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::generateParenthesis;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
1       ["()"]
2       ["()()","(())"]
3       ["()()()","()(())","(())()","(()())","((()))"]
)cases");
