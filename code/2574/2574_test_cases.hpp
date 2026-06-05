#pragma once

#include "2574.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::leftRightDifference;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[10,4,8,3] [15,1,11,22]
[1] [0]
)");
