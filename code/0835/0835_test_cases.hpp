#ifndef LEETCODE_0835_TEST_CASES_HPP
#define LEETCODE_0835_TEST_CASES_HPP

#include "0835.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::largestOverlap;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[[1,1,0],[0,1,0],[0,1,0]]
[[0,0,0],[0,1,1],[0,0,1]]
3
[[1]]
[[1]]
1
[[0]]
[[0]]
0
[[1,0,0,0],[0,0,0,0],[0,0,1,0],[0,0,0,0]]
[[0,0,0,0],[0,1,0,0],[0,0,0,0],[0,0,0,1]]
2
[[0,0,0,0],[0,0,0,0],[1,1,1,0],[0,0,0,0]]
[[0,1,1,1],[0,0,0,0],[0,0,0,0],[0,0,0,0]]
3
)");

#endif
