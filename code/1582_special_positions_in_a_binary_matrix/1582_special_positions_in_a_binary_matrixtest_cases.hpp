#pragma once

#include <string_view>

#include "1582_special_positions_in_a_binary_matrix.hpp"

inline static constexpr auto kMethodToTest = &Solution::numSpecial;
inline static constexpr std::string_view kTestCases = R"(
[[1,0,0],[0,0,1],[1,0,0]]
1

[[1,0,0],[0,1,0],[0,0,1]]
3

)";
