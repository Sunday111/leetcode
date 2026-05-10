#pragma once

#include "2770.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::maximumJumps;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,3,6,4,1,2] 2 3
[1,3,6,4,1,2] 3 5
[1,3,6,4,1,2] 0 -1
)");
