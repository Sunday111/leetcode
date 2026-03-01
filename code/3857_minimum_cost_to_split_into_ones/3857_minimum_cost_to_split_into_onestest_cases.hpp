#pragma once

#include <string_view>

#include "3857_minimum_cost_to_split_into_ones.hpp"

inline static constexpr auto kMethodToTest = &Solution::minCost;
inline static constexpr std::string_view kTestCases = R"(
3
3

4
6

500
124750
)";
