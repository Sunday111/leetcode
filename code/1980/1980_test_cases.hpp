#pragma once

#include "1980.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest =
    &Solution::findDifferentBinaryString;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
["01","10"]
"11"

["00","01"]
"10"

["111","011","001"]
"000"
)");
