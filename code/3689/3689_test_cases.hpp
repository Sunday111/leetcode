#pragma once

#include "3689.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::maxTotalValue;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,3,2]
2
4

[4,2,5,1]
3
12


)");
