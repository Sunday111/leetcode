#pragma once

#include "3548.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::canPartitionGrid;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[[1,4],[2,3]]
true

[[1,2],[3,4]]
true

[[1,2,4],[2,3,5]]
false

[[4,1,8],[3,2,6]]
false

[[1],[2],[1],[1],[1]]
true

[[1,2,1,1,1]]
true

[[1,1,1,2,1]]
true

[[73816],[71688]]
false

[[10,5,4,5]]
false

[[100000],[86218],[100000]]
true

[[5,5,6,2,2,2]]
true

[[25372],[100000],[100000]]
true

[[1,1],[2,1],[4,3]]
false

[[2190,608,1685],[22556,4932,16279],[1566,137,14025]]
true

[[2190,608,1685],[22556,4932,16279],[1566,137,14025]]
true
)");
