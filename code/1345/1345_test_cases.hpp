#pragma once

#include "1345.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::minJumps;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[100,-23,-23,404,100,23,23,23,3,404]    3
[7]                                     0
[7,6,9,6,9,6,9,7]                       1
)");
