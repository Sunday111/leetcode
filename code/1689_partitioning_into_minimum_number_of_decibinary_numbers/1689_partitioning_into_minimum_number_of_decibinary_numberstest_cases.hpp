#pragma once

#include <string_view>

#include "1689_partitioning_into_minimum_number_of_decibinary_numbers.hpp"

inline static constexpr auto kMethodToTest = &Solution::minPartitions;
inline static constexpr std::string_view kTestCases = R"(
"32"
3

"82734"
8

"27346209830709182346"
9

)";
