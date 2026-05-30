#pragma once

#include "2126.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::asteroidsDestroyed;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
10
[3,9,19,5,21]
true
5
[4,9,23,4]
false
)");
