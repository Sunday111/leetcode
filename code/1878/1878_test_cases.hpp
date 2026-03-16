#pragma once

#include "1878.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::getBiggestThree;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[[20,17, 9,13, 5, 2, 9, 1, 5],
 [14, 9, 9, 9,16,18, 3, 4,12],
 [18,15,10,20,19,20,15,12,11],
 [19,16,19,18, 8,13,15,14,11],
 [ 4,19, 5, 2,19,17, 7, 2, 2]
]
[107,103,102]


[[ 3, 4,  5, 1, 3],
 [ 3, 3,  4, 2, 3],
 [20,30,200,40,10],
 [ 1, 5,  5, 4, 1],
 [ 4, 3,  2, 2, 5]
]
[228,216,211]

[[1,2,3],[4,5,6],[7,8,9]]
[20,9,8]

[[7,7,7]]
[7]



)");
