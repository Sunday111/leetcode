#pragma once

#include "3471.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::largestInteger;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[3,9,2,1,7]
3
7

[3,9,7,2,1,7]
4
3

[0,0]
1
-1


)");
