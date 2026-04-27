#pragma once

#include "1391.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::hasValidPath;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[[2,4,3],[6,5,2]] true
[[1,2,1],[1,2,1]] false
[[1,1,2]]         false
)");
