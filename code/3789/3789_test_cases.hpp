#pragma once

#include "3789.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::minimumCost;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
3
2
1
3
2
3

5
4
15
2
3
22

5
4
15
0
0
0


)");
