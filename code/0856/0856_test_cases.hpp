#pragma once

#include "0856.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::scoreOfParentheses;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(

)");
