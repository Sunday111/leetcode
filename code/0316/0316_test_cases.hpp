#pragma once

#include "0316.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::removeDuplicateLetters;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"bcabc"    "abc"
"cbacdcbc" "acdb"
)");
