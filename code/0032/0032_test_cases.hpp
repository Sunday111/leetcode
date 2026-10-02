#pragma once

#include "0032.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::longestValidParentheses;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"(()"           2
")()())"        4
""              0
")()())()()("   4
)cases");
