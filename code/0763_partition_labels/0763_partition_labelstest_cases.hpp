#pragma once

#include <string_view>

#include "0763_partition_labels.hpp"

inline static constexpr auto kMethodToTest = &Solution::partitionLabels;
inline static constexpr std::string_view kTestCases = R"(
"ababcbacadefegdehijhklij"
[9,7,8]

"eccbbbbdec"
[10]
)";
