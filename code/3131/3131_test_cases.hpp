#pragma once

#include "3131.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::addedInteger;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[2,6,4]
[9,7,5]
3

[10]
[5]
-5

[1,1,1,1]
[1,1,1,1]
0


)");
