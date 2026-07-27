#pragma once

#include "3517.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::smallestPalindrome;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"z"
"z"

"babab"
"abbba"

"daccad"
"acddca"


)");
