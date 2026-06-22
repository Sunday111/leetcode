#pragma once

#include "1189.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::maxNumberOfBalloons;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"nlaebolko"
1
"loonbalxballpoon"
2
"leetcode"
0
)");
