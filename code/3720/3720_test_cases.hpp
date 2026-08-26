#pragma once

#include "3720.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::lexGreaterPermutation;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"abc"
"bba"
"bca"

"leet"
"code"
"eelt"

"baba"
"bbaa"
""


)");
