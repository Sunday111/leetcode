#pragma once

#include "2078.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::maxDistance;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,1,1,6,1,1,1] 3
[1,8,3,8,3] 4
[0,1] 1
)");
