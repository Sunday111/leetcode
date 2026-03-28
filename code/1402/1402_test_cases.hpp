#pragma once

#include "1402.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::maxSatisfaction;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[-1,-8,0,5,-7]
14
[4,3,2]
20
[-1,-4,-5]
0
)");
