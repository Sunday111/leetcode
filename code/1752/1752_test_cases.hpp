#pragma once

#include "1752.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::check;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[3,4,5,1,2] true
[2,1,3,4] false
[1,2,3] true
)");
