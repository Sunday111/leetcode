#pragma once

#include "2948.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest =
    &Solution::lexicographicallySmallestArray;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,5,3,9,8] 2 [1,3,5,8,9]
[1,7,6,18,2,1] 3 [1,6,7,18,1,2]
[1,7,28,19,10] 3 [1,7,28,19,10]
)");
