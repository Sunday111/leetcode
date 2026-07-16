#pragma once

#include "1979.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::findGCD;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[2,5,6,9,10] 2
[7,5,6,8,3]  1
[3,3]        3
)");
