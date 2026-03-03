#pragma once

#include <string_view>

#include "0078_subsets.hpp"

inline static constexpr auto kMethodToTest = &Solution::subsets;
inline static constexpr std::string_view kTestCases = R"(
[1,2,3]
[[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
)";
