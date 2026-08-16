#pragma once

#include "2029.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::stoneGameIX;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[2,1]           true
[2]             false
[5,1,2,4,3]     false
[20,3,20,17,2,12,15,17,4] true
)");
