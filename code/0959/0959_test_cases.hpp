#pragma once

#include "0959.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::regionsBySlashes;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[" /","/ "]     2
[" /","  "]     1
["/\","\/"]   5
)");
