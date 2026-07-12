#pragma once

#include "1291.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::sequentialDigits;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
100
300
[123, 234]

1000
13000
[1234,2345,3456,4567,5678,6789,12345]
)");
