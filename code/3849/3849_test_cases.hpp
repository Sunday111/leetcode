#pragma once

#include "3849.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::maximumXor;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"101"
"011"
"110"

"0110"
"1110"
"1101"

"0101"
"1001"
"1111"


)");
