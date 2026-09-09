#pragma once

#include "0940.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::distinctSubseqII;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"abc" 7
"aba" 6
"aaa" 3
)");
