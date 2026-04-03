#pragma once

#include "2087.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::minCost;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,0]
[2,3]
[5,4,3]
[8,2,6,7]
18

[0,0]
[0,0]
[5]
[26]
0
)");
