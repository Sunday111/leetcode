#pragma once

#include "3718.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::missingMultiple;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[8,2,3,4,6]
2
10

[1,4,7,10,15]
5
5


)");
