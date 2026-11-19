#pragma once

#include <string_view>

#include "1689.hpp"

inline static constexpr auto kMethodToTest = &Solution::minPartitions;
inline static constexpr std::string_view kTestCases = R"(
"32"
3

"82734"
8

"27346209830709182346"
9

)";
