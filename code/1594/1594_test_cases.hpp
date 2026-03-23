#pragma once

#include "1594.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::maxProductPath;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[[-1,-2,-3],[-2,-3,-3],[-3,-3,-2]]
-1

[[1,-2,1],[1,-2,1],[3,-4,1]]
8

[[1,3],[0,-4]]
0
)");
