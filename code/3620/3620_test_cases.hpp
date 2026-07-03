#pragma once

#include "3620.hpp"
#include "test_cases_helpers.hpp"
/*
 */

inline static constexpr auto kMethodToTest = &Solution::findMaxPathScore;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[[0,1,5],[1,3,10],[0,2,3],[2,3,4]]
[true,true,true,true]
10
3

[[0,1,7],[1,4,5],[0,2,6],[2,3,6],[3,4,2],[2,4,6]]
[true,true,true,false,true]
12
6

[[7,12,5],[0,4,41],[10,12,75],[9,12,17],[8,11,95],[3,6,82],[0,5,3],[2,5,16],[1,10,96],[1,8,45],[1,2,59],[5,12,21],[11,12,13],[9,10,49],[7,11,48],[4,8,20],[6,7,32],[4,10,36],[10,11,37],[1,6,6],[5,8,62],[6,9,23],[0,2,38],[4,11,92],[8,9,8],[2,6,28],[0,7,27],[0,8,78],[5,11,27],[4,7,11],[3,12,27],[5,9,70],[4,12,54],[6,11,78],[8,12,55],[2,11,40],[3,9,90],[1,11,4],[0,6,69],[7,8,57],[1,12,6]]
[true,true,false,true,true,false,true,false,true,true,true,false,true]
92
8

[[0,1,8]]
[true,true]
11
8
)");
