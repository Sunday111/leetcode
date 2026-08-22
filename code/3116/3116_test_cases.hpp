#pragma once

#include "3116.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::findKthSmallest;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[3,6,9]
3
9

[5,2]
7
12


)");
