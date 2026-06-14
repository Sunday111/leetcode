#pragma once

#include "2130.hpp"
#include "leet_code_list.hpp"  // IWYU pragma: keep
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::pairSum;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[5,4,2,1] 6
[4,2,2,3] 7
[1,100000] 100001
)");
