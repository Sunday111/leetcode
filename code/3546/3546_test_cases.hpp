#pragma once

#include "3546.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::canPartitionGrid;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[[1,4],[2,3]]
true

[[1,3],[2,4]]
false


)");
