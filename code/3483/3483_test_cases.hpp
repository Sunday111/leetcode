#pragma once

#include "3483.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::totalNumbers;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,2,3,4]
12

[0,2,2]
2

[6,6,6]
1

[1,3,5]
0


)");
