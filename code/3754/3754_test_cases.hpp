#pragma once

#include "3754.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::sumAndMultiply;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
10203004
12340

1000
1


)");
