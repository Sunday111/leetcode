#pragma once

#include "2405.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::partitionString;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"abacaba" 4

"ssssss" 6
)");
