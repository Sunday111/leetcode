#pragma once

#include "0151.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::reverseWords;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"the sky is blue"       "blue is sky the"
"  hello world  "       "world hello"
"a good   example"      "example good a"
)");
