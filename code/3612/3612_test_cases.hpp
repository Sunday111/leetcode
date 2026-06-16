#pragma once

#include "3612.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::processStr;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"a#b%*"
"ba"

"z*#"
""


)");
