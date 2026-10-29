#pragma once

#include "3841.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::palindromePath;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
3
[[0,1],[1,2]]
"aac"
["query 0 2","update 1 b","query 0 2"]
[true,false]

4
[[0,1],[0,2],[0,3]]
"abca"
["query 1 2","update 0 b","query 2 3","update 3 a","query 1 3"]
[false,false,true]


)");
