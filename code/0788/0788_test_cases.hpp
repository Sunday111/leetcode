#pragma once

#include "0788.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::rotatedDigits;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
10 4
1  0
2  1
)");
