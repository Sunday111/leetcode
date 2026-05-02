#pragma once

#include "0796.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::rotateString;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"abcde"
"cdeab"
true

"abcde"
"abced"
false
)");
