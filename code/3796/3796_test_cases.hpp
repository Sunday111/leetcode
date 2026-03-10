#pragma once

#include "3796.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::findMaxVal;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
10
[[3,1],[8,1]]
[2,2,3,1,4,5,1,1,2]
6

8
[[3,2]]
[3,5,2,4,2,3,1]
12


)");
