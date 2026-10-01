#pragma once

#include "0020.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::isValid;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"()"
true

"()[]{}"
true

"(]"
false

"([])"
true

"([)]"
false


)cases");
