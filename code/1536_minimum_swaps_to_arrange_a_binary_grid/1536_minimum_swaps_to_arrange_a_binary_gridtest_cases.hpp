#pragma once

#include <string_view>

#include "1536_minimum_swaps_to_arrange_a_binary_grid.hpp"

inline static constexpr auto kMethodToTest = &Solution::minSwaps;
inline static constexpr std::string_view kTestCases = R"(
[[0,0,1],[1,1,0],[1,0,0]]
3

[[0,1,1,0],[0,1,1,0],[0,1,1,0],[0,1,1,0]]
-1

[[1,0,0],[1,1,0],[1,1,1]]
0

)";
