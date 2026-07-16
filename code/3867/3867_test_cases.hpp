#pragma once

#include "3867.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::gcdSum;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[2,6,4]
2

[3,6,2,8]
5


)");
