#pragma once

#include "1340.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::maxJumps;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[6,4,14,6,8,13,9,7,10,6,12]
2
4
[3,3,3,3,3]
3
1
[7,6,5,4,3,2,1]
1
7
)");
