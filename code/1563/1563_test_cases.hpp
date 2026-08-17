#pragma once

#include "1563.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::stoneGameV;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[6,2,3,4,5,5]               18
[7,7,7,7,7,7,7]             28
[4]                         0
)");
