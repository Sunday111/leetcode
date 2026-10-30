#pragma once

#include "3970.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::shortestPath;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
3
[[0,1,1],[1,2,1],[0,2,3]]
"aab"
1
3

3
[[0,1,1],[1,2,1],[0,2,3]]
"aab"
2
2

3
[[0,1,1],[1,2,1]]
"aaa"
2
-1


)");
