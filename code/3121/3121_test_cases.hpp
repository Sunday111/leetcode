#pragma once

#include "3121.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::numberOfSpecialChars;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"aaAbcBC"
3

"abc"
0

"AbBCab"
0


)");
