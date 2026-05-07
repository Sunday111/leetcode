#pragma once

#include "0442.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::findDuplicates;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[4,3,2,7,8,2,3,1] [2,3]
[1,1,2]           [1]
[1]               []
)");
