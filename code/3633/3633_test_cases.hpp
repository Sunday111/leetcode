#pragma once

#include "3633.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::earliestFinishTime;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[2,8]
[4,1]
[6]
[3]
9

[5]
[3]
[1]
[10]
14


)");
