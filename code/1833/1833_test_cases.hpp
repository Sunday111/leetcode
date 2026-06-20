#pragma once

#include "1833.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::maxIceCream;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,3,2,4,1]     7 4
[10,6,8,7,7,8]  5 0
[1,6,3,1,2,5]  20 6
)");
