#pragma once

#include "3418.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::maximumAmount;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[[0,1,-1],[1,-2,3],[2,-3,4]]
8

[[10,10,10],[10,10,10]]
40


)");
