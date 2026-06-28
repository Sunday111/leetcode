#pragma once

#include "1967.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::numOfStrings;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
["a","abc","bc","d"] "abc"          3
["a","b","c"]        "aaaaabbbbb"   2
["a","a","a"]        "ab"           3
)");
