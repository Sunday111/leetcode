#pragma once

#include "3699.hpp"
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

4
1
5
170

)");
