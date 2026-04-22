#pragma once

#include "2452.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::twoEditWords;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
["word","note","ants","wood"]
["wood","joke","moat"]
["word","note","wood"]

["yes"]
["not"]
[]
)");
