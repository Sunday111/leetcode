#pragma once

#include "1871.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::canReach;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"011010"
2
3
true

"01101110"
2
3
false
)");
