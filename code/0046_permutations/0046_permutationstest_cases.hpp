#pragma once

#include <string_view>

#include "0046_permutations.hpp"

inline static constexpr auto kMethodToTest = &Solution::permute;
inline static constexpr std::string_view kTestCases = R"(
[1,2,3]
[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]

[0,1]
[[0,1],[1,0]]

[1]
[[1]]
)";
