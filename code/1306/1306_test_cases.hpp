#pragma once

#include "1306.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::canReach;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[4,2,3,0,3,1,2]
5
true
[4,2,3,0,3,1,2]
0
true
[3,0,2,1,2]
2
false
)");
