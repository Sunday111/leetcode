#pragma once

#include "2784.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::isGood;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[2, 1, 3] false
[1, 3, 3, 2] true
[1, 1] true
[3, 4, 4, 1, 2, 1] false
)");
