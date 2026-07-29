#pragma once

#include "1406.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::stoneGameIII;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,2,3,7]       "Bob"
[1,2,3,-9]      "Alice"
[1,2,3,6]       "Tie"
[-1,-2,-3]      "Tie"
)");
