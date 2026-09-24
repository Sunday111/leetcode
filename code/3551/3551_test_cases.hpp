#pragma once

#include "3551.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::minSwaps;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[3,1,2]
2

[18,43,34,16]
2

[22,14,33,7]
0

[37,100]
1

)");
