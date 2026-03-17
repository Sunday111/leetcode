#pragma once

#include "1074.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::numSubmatrixSumTarget;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[[0,1,0],[1,1,1],[0,1,0]]
0
4

[[1,-1],[-1,1]]
0
5

[[904]]
0
0
)");
