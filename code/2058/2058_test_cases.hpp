#pragma once

#include "2058.hpp"
#include "leet_code_list.hpp"  // IWYU pragma: keep
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest =
    &Solution::nodesBetweenCriticalPoints;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[3,1]                   [-1,-1]
[5,3,1,2,5,1,2]         [1,3]
[1,3,2,2,3,2,2,2,7]     [3,3]
)");
