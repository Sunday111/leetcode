#pragma once

#include "2540.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::getCommon;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,2,3]
[2,4]
2
[1,2,3,6]
[2,3,4,5]
2
)");
