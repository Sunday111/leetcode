#pragma once

#include "0396.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::maxRotateFunction;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[4,3,2,6] 26
[100] 0
)");
