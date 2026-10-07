#pragma once

#include "0856.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::scoreOfParentheses;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"()" 1
"(())" 2
"()()" 2
"(()(()))" 6
"((()))" 4
"(()())" 4
"(())()" 3
"()(())" 3
"(()())(())" 6
"((())())" 6
"((()()))" 8
"()()()()()()()()()()()()()()()()()()()()()()()()()" 25
"((((((((((((((((((((((((()))))))))))))))))))))))))" 16777216
)cases");
