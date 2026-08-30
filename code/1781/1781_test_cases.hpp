#pragma once

#include "1781.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::beautySum;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
    "aabcb"     5
    "aabcbaa"   17
)");
