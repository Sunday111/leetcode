#pragma once

#include "3310.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::remainingMethods;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
4
1
[[1,2],[0,1],[3,2]]
[0,1,2,3]

5
0
[[1,2],[0,2],[0,1],[3,4]]
[3,4]

3
2
[[1,2],[0,1],[2,0]]
[]

4
0
[[2,3],[1,2]]
[1,2,3]

3
2
[[1,0],[2,0]]
[0,1,2]
)");
