#pragma once

#include "1641.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::countVowelStrings;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
1
5

2
15

33
66045

50
316251
)");
