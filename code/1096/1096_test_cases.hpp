#pragma once

#include "1096.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::braceExpansionII;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"{a,b}{c,{d,e}}"        ["ac","ad","ae","bc","bd","be"]
"{{a,z},a{b,c},{ab,z}}" ["a","ab","ac","z"]
"{a,{c,d}}"             ["a","c","d"]
)");
