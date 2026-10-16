#pragma once

#include "1569.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::numOfWays;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1] 0
[1,2] 0
[2,1] 0
[1,2,3,4,5] 0
[5,4,3,2,1] 0
[2,1,3] 1
[3,1,2,4] 2
[3,4,1,2] 2
[3,4,5,1,2] 5
[4,2,1,3,6,5,7] 79
[8,4,2,1,3,6,5,7,12,10,9,11,14,13,15] 21964799
[16,8,4,2,1,3,6,5,7,12,10,9,11,14,13,15,24,20,18,17,19,22,21,23,28,26,25,27,30,29,31] 203434153
)");
