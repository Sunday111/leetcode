#pragma once

#include "2812.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::maximumSafenessFactor;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[[1,0,0],[0,0,0],[0,0,1]]                       0
[[0,0,1],[0,0,0],[0,0,0]]                       2
[[0,0,0,1],[0,0,0,0],[0,0,0,0],[1,0,0,0]]       2
)");
