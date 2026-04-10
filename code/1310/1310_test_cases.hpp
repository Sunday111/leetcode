#pragma once

#include "1310.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::xorQueries;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,3,4,8]
[[0,1],[1,2],[0,3],[3,3]]
[2,7,14,8]

[4,8,2,10]
[[2,3],[1,3],[0,0],[0,3]]
[8,0,4,4]
)");
