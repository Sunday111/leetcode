#pragma once

#include "0301.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest =
    &Solution::removeInvalidParentheses;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"()())()"       ["(())()","()()()"]
"(a)())()"      ["(a())()","(a)()()"]
")("            [""]
"(a()"          ["a()","(a)"]
"(a(b)"         ["a(b)","(ab)"]
")a)b(c("       ["abc"]
"abc"           ["abc"]
"abcdefghijklmnoqrstuvwxyz" ["abcdefghijklmnoqrstuvwxyz"]
"((((((((((abcde))))))))))" ["((((((((((abcde))))))))))"]
)cases");
