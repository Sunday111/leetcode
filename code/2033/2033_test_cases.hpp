#pragma once

#include "2033.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::minOperations;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[[2,4],[6,8]] 2 4
[[1,5],[2,3]] 1 5
[[1,2],[3,4]] 2 -1
)");
