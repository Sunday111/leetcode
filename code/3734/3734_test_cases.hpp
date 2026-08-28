#pragma once

#include "3734.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest =
    &Solution::lexPalindromicPermutation;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"baba"
"abba"
"baab"

"baba"
"bbaa"
""

"abc"
"abb"
""

"aac"
"abb"
"aca"

"a"
"z"
""
)");
