#pragma once

#include "1464.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::maxProduct;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[3,4,5,2]   12
[1,5,4,5]   16
[3,7]       12
)");
