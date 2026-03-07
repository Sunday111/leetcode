#pragma once

#include "1888_minimum_number_of_flips_to_make_the_binary_string_alternating.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::minFlips;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"111000"
2

"010"
0

"1110"
1

)");
