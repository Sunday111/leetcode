#pragma once

#include "3600.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::maxStability;
// inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(

// 5
// [[0,1,3,0],[1,2,6,1],[2,3,2,0],[3,4,5,0],[0,4,1,0]]
// 2
// 4

// )");

inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
3
[[0,1,2,1],[1,2,3,0]]
1
2

3
[[0,1,4,0],[1,2,3,0],[0,2,1,0]]
2
6

3
[[0,1,1,1],[1,2,1,1],[2,0,1,1]]
0
-1

5
[[0,1,3,0],[1,2,6,1],[2,3,2,0],[3,4,5,0],[0,4,1,0]]
2
4

)");
