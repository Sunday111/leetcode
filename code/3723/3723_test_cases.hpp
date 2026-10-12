#pragma once

#include "3723.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::maxSumOfSquares;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
2
3
"30"

2
17
"98"

1
10
""


)");
