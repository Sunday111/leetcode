#pragma once

#include "0657.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::judgeCircle;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"UD" true
"LL" false
)");
