#pragma once

#include "2685.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::countCompleteComponents;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
6 [[0,1],[0,2],[1,2],[3,4]]       3
6 [[0,1],[0,2],[1,2],[3,4],[3,5]] 1
)");
