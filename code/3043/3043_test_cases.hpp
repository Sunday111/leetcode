#pragma once

#include "3043.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::longestCommonPrefix;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,10,100]
[1000]
3

[1,2,3]
[4,4,4]
0
)");
