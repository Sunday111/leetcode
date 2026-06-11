#pragma once

#include "3558.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::assignEdgeWeights;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[[1,2]]
1

[[1,2],[1,3],[3,4],[3,5]]
2


)");
