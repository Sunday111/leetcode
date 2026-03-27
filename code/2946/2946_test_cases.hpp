#pragma once

#include "2946.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::areSimilar;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[[1,2,3],[4,5,6],[7,8,9]]
4
false

[[1,2,1,2],[5,5,5,5],[6,3,6,3]]
2
true

[[2,2],[2,2]]
3
true


)");
