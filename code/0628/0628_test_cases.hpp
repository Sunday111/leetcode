#pragma once

#include "0628.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::maximumProduct;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[-2,-1,3,4,5]               60
[0,-1,0,-2,-1,1]            2
[-2,-3,-1,0,-8]             0
[-7,-2,2,-1,-4]             56
[1,-2,2,-12,-17]            408
[-1,-2,-3,5,-4]             60
[-9,2,-10,5,-3,8,-7,4,-1]   720
[-1,-2,-3]                  -6
[-1,-2,-3,-4]               -6
)");
