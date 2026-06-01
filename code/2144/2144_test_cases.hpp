#pragma once

#include "2144.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::minimumCost;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,2,3] 5
[6,5,7,9,2,2] 23
[5,5] 10
)");
