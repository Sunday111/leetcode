#pragma once

#include "2309.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::greatestLetter;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"lEeTcOdE" "E"
"arRAzFif" "R"
"AbCdEfGhIjK" ""
)");
