#pragma once

#include "2840.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::checkStrings;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"abcdba"
"cabdab"
true

"abe"
"bea"
false
)");
