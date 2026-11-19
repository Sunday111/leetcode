#pragma once

#include <string_view>

#include "1347.hpp"

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
