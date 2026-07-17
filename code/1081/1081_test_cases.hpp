#pragma once

#include "1081.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::smallestSubsequence;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"bcabc"     "abc"
"cbacdcbc"  "acdb"
)");
