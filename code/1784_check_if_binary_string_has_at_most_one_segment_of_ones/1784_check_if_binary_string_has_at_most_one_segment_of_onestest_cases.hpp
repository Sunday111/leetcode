#pragma once

#include <string_view>

#include "1784_check_if_binary_string_has_at_most_one_segment_of_ones.hpp"

inline static constexpr auto kMethodToTest = &Solution::checkOnesSegment;
inline static constexpr std::string_view kTestCases = R"(
"1001"
false

"110"
true

)";
