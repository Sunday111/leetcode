#pragma once

#include "1855.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::maxDistance;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[55,30,5,4,2]
[100,20,10,10,5]
2

[2,2,2]
[10,10,1]
1

[30,29,19,5]
[25,25,25,25,25]
2
)");
