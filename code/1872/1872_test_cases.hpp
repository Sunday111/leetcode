#pragma once

#include "1872.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::stoneGameVIII;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[7,-6,5,10,5,-2,-6] 13
[-1,2,-3,4,-5] 5
)");
