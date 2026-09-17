#pragma once

#include "1658.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::minOperations;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,1,4,2,3]         5       2
[5,6,7,8,9]         4       -1
[3,2,20,1,1,3]      10      5
[1,1]               3       -1
[5,2,3,1,1]         5       1
[2,3,1,1,1]         5       2
[1000,1,1,2,3]      1004    3
)");
