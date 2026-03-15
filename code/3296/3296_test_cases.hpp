#pragma once

#include "3296.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::minNumberOfSeconds;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
4
[2,1,1]
3

10
[3,2,2,4]
12

5
[1]
15

8
[1,1]
10

1
[5]
5

)");
