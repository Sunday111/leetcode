#pragma once

#include "1886.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::findRotation;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[[0,1],[1,0]]
[[1,0],[0,1]]
true

[[0,1],[1,1]]
[[1,0],[0,1]]
false

[[0,0,0],[0,1,0],[1,1,1]]
[[1,1,1],[0,1,0],[0,0,0]]
true

[[1]]
[[0]]
false
)");
