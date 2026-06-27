#pragma once

#include "0010.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::isMatch;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"aa" "a*" true
"ab" ".*" true
"mississippi" "mis*is*ip*." true
"bbbba" ".*a*a" true
"a" ".*..a*" false
"baa" ".ba" false
"bbab" "b*a*" false
"bbba" ".*b" false
)");
