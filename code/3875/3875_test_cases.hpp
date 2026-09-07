#pragma once

#include "3875.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::uniformArray;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[2,3]
true

[4,6]
true


)");
