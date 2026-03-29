#pragma once

#include "0773.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::slidingPuzzle;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[[1,2,3],[4,0,5]]
1
[[1,2,3],[5,4,0]]
-1
[[4,1,2],[5,0,3]]
5
[[1,3,4],[0,2,5]]
14
[[3,2,4],[1,5,0]]
14
[[2,4,1],[5,3,0]]
12
[[0,5,2],[4,3,1]]
15
[[4,2,0],[5,1,3]]
7
[[3,0,1],[4,2,5]]
-1
[[3,2,1],[4,0,5]]
-1
[[1,2,3],[4,5,0]]
0
)");
