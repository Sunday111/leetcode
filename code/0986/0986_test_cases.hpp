#pragma once

#include "0986.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::intervalIntersection;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[[0,2],[5,10],[13,23],[24,25]]
[[1,5],[8,12],[15,24],[25,26]]
[[1,2],[5,5],[8,10],[15,23],[24,24],[25,25]]

[[1,3],[5,9]]
[]
[]

[[0,2],[4,6],[8,12]]
[[1,10]]
[[1,2],[4,6],[8,10]]

[[0,2]]
[[1,3]]
[[1,2]]

[[0,10]]
[[1,2],[4,5]]
[[1,2],[4,5]]

[[0,1]]
[[2,3]]
[]

[]
[[1,2]]
[]
)");
