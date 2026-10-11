#pragma once

#include "2897.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::maxSum;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[2,6,5,8]           2  261
[4,5,4,7]           3  90
)");
