#pragma once

#include "1888.hpp"
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
