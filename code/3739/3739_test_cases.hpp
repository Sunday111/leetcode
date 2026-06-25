#pragma once

#include "3739.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::countMajoritySubarrays;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,2,2,3]
2
5

[1,1,1,1]
1
10

[1,2,3]
4
0


)");
