#pragma once

#include "3700.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::zigZagArrays;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
3
4
5
2

3
1
3
10

1000000000
1
75
16
)");
