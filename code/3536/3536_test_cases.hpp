#pragma once

#include "3536.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::maxProduct;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
31
3

22
4

124
8


)");
