#pragma once

#include "3474.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::generateString;

inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"TFTF"
"ab"
"ababa"

"TFTF"
"abc"
""

"F"
"d"
"a"

"FT"
"wvxyy"
"awvxyy"

"TTFFT"
"fff"
""

"FFFF"
"ddb"
"aaaaaa"

"FFTFFF"
"a"
"bbabbb"

"FTFTFFTFFFTFFFF"
"vyv"
"avyvyvvyvavyvaaaa"

"FTFTFFTFFFTFFFF"
"vyv"
"avyvyvvyvavyvaaaa"
)");

/*
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"TFTF"
"ab"
"ababa"
)");
*/
