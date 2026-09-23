#pragma once

#include "3550.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::smallestIndex;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,3,2]
2

[1,10,11]
1

[1,2,3]
-1


)");
