#pragma once

#include "1559.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::containsCycle;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[["a","a","a","a"],["a","b","b","a"],["a","b","b","a"],["a","a","a","a"]] true
[["c","c","c","a"],["c","d","c","c"],["c","c","e","c"],["f","c","c","c"]] true
[["a","b","b"],["b","z","b"],["b","b","a"]] false
[["b","c","d","e","a","a","a"],["a","a","a","f","a","g","a"],["a","h","a","a","a","i","a"],["a","j","k","l","m","n","a"],["a","a","a","a","a","a","a"]] true
[["b","c","a","a"],["d","a","a","a"],["a","b","a","c"]] true
)");
