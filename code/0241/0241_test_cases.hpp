#pragma once

#include "0241.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::diffWaysToCompute;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"2*3-4*5"   [-34,-14,-10,-10,10]
"2-1-1"     [0,2]
)");
