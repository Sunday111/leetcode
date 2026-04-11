#pragma once

#include "3740.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::minimumDistance;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,2,1,1,3]
6

[1,1,2,3,2,1,2]
8

[1]
-1


)");
