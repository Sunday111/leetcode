#pragma once

#include "1727.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::largestSubmatrix;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[[0,0,1],[1,1,1],[1,0,1]]
4
[[1,0,1,0,1]]
3
[[1,1,0],[1,0,1]]
2
)");
