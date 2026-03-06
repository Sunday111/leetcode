#pragma once

#include <string_view>

#include "2130_maximum_twin_sum_of_a_linked_list.hpp"

inline static constexpr auto kMethodToTest = &Solution::pairSum;
inline static constexpr std::string_view kTestCasesText = R"(
[5,4,2,1]
6

[4,2,2,3]
7

[1,100000]
100001
)";
