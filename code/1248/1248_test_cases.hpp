#pragma once

#include "1248.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::numberOfSubarrays;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,1,2,1,1]
3
2
[2,4,6]
1
0
[2,2,2,1,2,2,1,2,2,2]
2
16
)");
