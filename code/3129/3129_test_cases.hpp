#pragma once

#include "3129.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::numberOfStableArrays;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
1
1
2
2

1
2
1
1

3
3
2
14

39
20
18
207227572


)");
