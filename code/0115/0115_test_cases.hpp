#pragma once

#include "0115.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::numDistinct;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"rabbbit"   "rabbit"  3
"babgbag"   "bag"     5
)");
