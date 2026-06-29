#pragma once

#include "1358.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::numberOfSubstrings;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"abcabc" 10
"aaacb"  3
"abc"    1
)");
