#pragma once

#include "1334.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::findTheCity;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
4
[[0,1,3],[1,2,1],[1,3,4],[2,3,1]]
4
3

5
[[0,1,2],[0,4,8],[1,2,3],[1,4,2],[2,3,1],[3,4,1]]
2
0
)");
