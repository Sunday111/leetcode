#pragma once

#include "1846.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest =
    &Solution::maximumElementAfterDecrementingAndRearranging;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[2,2,1,2,1]     2
[100,1,1000]    3
[1,2,3,4,5]     5
)");
