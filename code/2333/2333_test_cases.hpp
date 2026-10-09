#pragma once

#include "2333.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::minSumSquareDiff;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(

[1,4,10,12]
[5,8,6,9]
1
1
43

[1,2,3,4]
[2,10,20,19]
0
0
579
)");
