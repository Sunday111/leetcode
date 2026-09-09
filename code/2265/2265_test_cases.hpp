#pragma once

#include "2265.hpp"
#include "leet_code_binary_tree.hpp"  // IWYU pragma: keep
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::averageOfSubtree;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[4,8,5,0,1,null,6]  5
[1]                 1
)");
