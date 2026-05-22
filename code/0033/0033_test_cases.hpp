#pragma once

#include "0033.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::search;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[4,5,6,7,0,1,2]
0
4

[4,5,6,7,0,1,2]
3
-1

[1]
0
-1
)");
