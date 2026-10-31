#pragma once

#include "3665.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::uniquePaths;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[[0,1,0],[0,0,1],[1,0,0]]
5

[[0,0],[0,0]]
2

[[0,1,1],[1,1,0]]
1

[[0,0],[1,0],[0,0]]
2

[[0,0,0],[1,1,0],[0,0,0]]
3

[[0,0],[1,1],[0,1],[0,0]]
0

[[0,1,1,1],[1,1,1,1],[1,1,1,1],[1,1,1,0]]
2

[[0,0,0,0],[0,0,0,0],[0,0,0,0]]
10

)");
