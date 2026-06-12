#pragma once

#include "3559.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::assignEdgeWeights;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[[1,2]]
[[1,1],[1,2]]
[0,1]

[[1,2],[1,3],[3,4],[3,5]]
[[1,4],[3,4],[2,5]]
[2,1,4]


)");
