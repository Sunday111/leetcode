#pragma once

#include "0153.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::findMin;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[3,4,5,1,2] 1
[4,5,6,7,0,1,2] 0
[11,13,15,17] 11
)");
