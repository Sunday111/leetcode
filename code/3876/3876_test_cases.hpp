#pragma once

#include "3876.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::uniformArray;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,4,7]
true

[2,3]
false

[4,6]
true


)");
