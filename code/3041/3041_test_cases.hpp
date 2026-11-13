#pragma once

#include "3041.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::maxSelectedElements;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,3]      2
[1,4,7,10]  1
[1,2,2]    3
[2,1,5,1,1] 3
[1] 1
[1000000] 1
[1,1,1,1] 2
[1000000,1000000] 2
[1,1,3,3,5,5] 6
[1,2,4] 3
[63,64,65,65,66] 5
)");
