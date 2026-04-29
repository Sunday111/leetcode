#pragma once

#include "3225.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::maximumScore;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[[0,0,0,0,0],[0,0,3,0,0],[0,1,0,0,0],[5,0,0,3,0],[0,0,0,0,2]]
11

[[10,9,0,0,15],[7,1,0,8,0],[5,20,0,11,0],[0,0,0,1,2],[8,12,1,10,3]]
94


)");
