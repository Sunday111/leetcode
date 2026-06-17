#pragma once

#include "1344.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::angleClock;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
12 30 165
 3 30  75
 3 15 7.5
)");
