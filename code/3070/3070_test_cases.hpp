#pragma once

#include "3070.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::countSubmatrices;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[[7,6,3],[6,6,1]]
18
4

[[7,2,9],[1,5,0],[2,6,6]]
20
6

[
 [1,10],
 [7,2],
 [9,1],
 [4,1]
]
8
2
)");
