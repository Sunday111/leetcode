#pragma once

#include "3629.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::minJumps;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,2,4,6]
2

[2,3,4,7,9]
2

[4,6,5,8]
3
)");

/*inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,2,4,6]
2

[2,3,4,7,9]
2

[4,6,5,8]
3


)");*/
