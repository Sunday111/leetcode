#pragma once

#include "3532.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::pathExistenceQueries;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
2
[1,3]
1
[[0,0],[0,1]]
[true,false]

4
[2,5,6,8]
2
[[0,1],[0,2],[1,3],[2,3]]
[false,false,true,true]


)");
