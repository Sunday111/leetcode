#pragma once

#include "2515.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::closestTarget;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
["hello","i","am","leetcode","hello"]
"hello"
1
1
["a","b","leetcode"]
"leetcode"
0
1
["i","eat","leetcode"]
"ate"
0
-1
)");
