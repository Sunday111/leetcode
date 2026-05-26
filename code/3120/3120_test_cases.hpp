#pragma once

#include "3120.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::numberOfSpecialChars;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"aaAbcBC"
3

"abc"
0


)");
