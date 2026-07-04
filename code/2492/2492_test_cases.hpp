#pragma once

#include "2492.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::minScore;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
4
[[1,2,9],[2,3,6],[2,4,5],[1,4,7]]
5

4
[[1,2,2],[1,3,4],[3,4,7]]
2

7
[[1,3,1484],[3,2,3876],[2,4,6823],[6,7,579],[5,6,4436],[4,5,8830]]
579

13
[[2,12,1891],[10,9,4138],[11,3,2007],[1,10,9390],[12,8,1915],[6,2,1098],[5,4,2795],[3,13,4562],[9,7,9202],[4,6,6752],[8,11,1480],[7,5,9827]]
1098

)");
