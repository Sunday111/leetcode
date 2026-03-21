#pragma once

#include "3643.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::reverseSubmatrix;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[[1,2,3,4],[5,6,7,8],[9,10,11,12],[13,14,15,16]]
1
0
3
[[1,2,3,4],[13,14,15,8],[9,10,11,12],[5,6,7,16]]

[[3,4,2,3],[2,3,4,2]]
0
2
2
[[3,4,4,2],[2,3,2,3]]


)");
