#pragma once

#include "3622.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::checkDivisibility;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
99
true

23
false


)");
