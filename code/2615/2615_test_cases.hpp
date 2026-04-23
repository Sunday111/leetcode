#pragma once

#include "2615.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::distance;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,3,1,1,2] [5,0,3,4,0]
[0,5,3]     [0,0,0]
)");
