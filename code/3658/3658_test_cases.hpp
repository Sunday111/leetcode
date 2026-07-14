#pragma once

#include "3658.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::gcdOfOddEvenSums;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
4
4

5
5


)");
