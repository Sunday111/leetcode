#pragma once

#include "2833.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest =
    &Solution::furthestDistanceFromOrigin;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"L_RL__R" 3
"_R__LL_" 5
"_______" 7
)");
