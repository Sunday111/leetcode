#pragma once

#include "2657.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest =
    &Solution::findThePrefixCommonArray;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,3,2,4]
[3,1,2,4]
[0,2,3,4]
[2,3,1]
[3,1,2]
[0,1,3]
)");
