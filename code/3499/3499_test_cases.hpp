#pragma once

#include "3499.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::maxActiveSectionsAfterTrade;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"01"
1

"0100"
4

"1000100"
7

"01010"
4


)");
