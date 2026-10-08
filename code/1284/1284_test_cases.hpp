#pragma once

#include "1284.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::minFlips;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[[0],[1],[1]]       1
[[0,1,1]]           1
[[0,0],[0,1]]       3
[[0]]               0
[[1,0,0],[1,0,0]]   -1
)");
