#pragma once

#include "1288.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::removeCoveredIntervals;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[[1,4],[3,6],[2,8]]     2
[[1,4],[2,3]]           1
)");
