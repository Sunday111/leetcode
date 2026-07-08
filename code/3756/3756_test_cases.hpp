#pragma once

#include "3756.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::sumAndMultiply;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"10203004"
[[0,7],[1,3],[4,6]]
[12340, 4, 9]

"1000"
[[0,3],[1,1]]
[1, 0]

"9876543210"
[[0,9]]
[444444137]


)");
