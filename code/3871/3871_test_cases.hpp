#pragma once

#include "3871.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::countCommas;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
1002
3

998
0


)");
