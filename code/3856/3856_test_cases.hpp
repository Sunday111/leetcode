#pragma once

#include "3856.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::trimTrailingVowels;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"idea"
"id"

"day"
"day"

"aeiou"
""


)");
