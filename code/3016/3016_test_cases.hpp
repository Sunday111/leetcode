#pragma once

#include "3016.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::minimumPushes;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"abcde"                     5
"xyzxyzxyzxyz"              12
"aabbccddeeffgghhiiiiii"    24
)");
