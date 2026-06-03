#pragma once

#include "3751.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::totalWaviness;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
120
130
3

198
202
3

4848
4848
2


)");
