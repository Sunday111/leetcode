#pragma once

#include "3300.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::minElement;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[10,12,13,14]
1

[1,2,3,4]
1

[999,19,199]
10


)");
