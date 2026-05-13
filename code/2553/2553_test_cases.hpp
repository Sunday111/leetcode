#pragma once

#include "2553.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::separateDigits;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[13,25,83,77] [1,3,2,5,8,3,7,7]
[7,1,3,9]     [7,1,3,9]
)");
