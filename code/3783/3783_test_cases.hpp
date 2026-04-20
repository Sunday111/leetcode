#pragma once

#include "3783.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::mirrorDistance;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
25
27

10
9

7
0


)");
