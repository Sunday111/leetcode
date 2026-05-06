#pragma once

#include "3660.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::maxValue;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[2,1,3]
[2,2,3]

[2,3,1]
[3,3,3]


)");
