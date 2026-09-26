#pragma once

#include "1807.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::evaluate;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"(name)is(age)yearsold"
[["name","bob"],["age","two"]]
"bobistwoyearsold"

"hi(name)"
[["a","b"]]
"hi?"
)cases");
