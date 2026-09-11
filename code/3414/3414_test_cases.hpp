#pragma once

#include "3414.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::maximumWeight;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[[1,3,2],[4,5,2],[1,5,5],[6,9,3],[6,7,1],[8,9,1]]
[2,3]

[[5,8,1],[6,7,7],[4,7,3],[9,10,6],[7,8,2],[11,14,3],[3,5,5]]
[1,3,5,6]

[[1,2,6],[3,4,6],[1,4,10],[5,6,100],[7,8,100],[9,10,100]]
[2,3,4,5]

[[1,1,1000000000],[2,2,1000000000],[3,3,1000000000],[4,4,1000000000]]
[0,1,2,3]


)");
