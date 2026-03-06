#pragma once

#include "____problem_name____.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::method_name;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"32"
3

"82734"
8

"27346209830709182346"
9

)");
