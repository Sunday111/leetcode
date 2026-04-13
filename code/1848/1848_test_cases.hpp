#pragma once

#include "1848.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::getMinDistance;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,2,3,4,5]
5
3
1

[1]
1
0
0

[1,1,1,1,1,1,1,1,1,1]
1
0
0
)");
