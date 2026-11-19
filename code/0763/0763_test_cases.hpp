#pragma once

#include <string_view>

#include "0763.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::partitionLabels;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"ababcbacadefegdehijhklij"
[9,7,8]

"eccbbbbdec"
[10]
)");
