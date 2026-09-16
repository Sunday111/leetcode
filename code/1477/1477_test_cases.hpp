#pragma once

#include "1477.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::minSumOfLengths;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[3,2,2,4,3]
3
2
[7,3,4,7]
7
2
[4,3,2,6,2,3,4]
6
-1
)");
