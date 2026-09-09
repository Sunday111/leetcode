#pragma once

#include "3903.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::firstStableIndex;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[5,0,1,4]
3
3

[3,2,1]
1
-1

[0]
0
0


)");
