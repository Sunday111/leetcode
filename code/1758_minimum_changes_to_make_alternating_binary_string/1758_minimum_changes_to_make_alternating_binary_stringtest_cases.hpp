#pragma once

#include <string_view>

#include "1758_minimum_changes_to_make_alternating_binary_string.hpp"

inline static constexpr auto kMethodToTest = &Solution::minOperations;
inline static constexpr std::string_view kTestCases = R"(
"0100"
1

"10"
0

"1111"
2

)";
