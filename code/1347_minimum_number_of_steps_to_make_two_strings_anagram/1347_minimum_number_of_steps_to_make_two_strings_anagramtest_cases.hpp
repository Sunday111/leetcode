#pragma once

#include <string_view>

#include "1347_minimum_number_of_steps_to_make_two_strings_anagram.hpp"

inline static constexpr auto kMethodToTest = &Solution::minSteps;
inline static constexpr std::string_view kTestCases = R"(
"bab"
"aba"
1

"leetcode"
"practice"
5

"anagram"
"mangaar"
0
)";
