#pragma once

#include <string_view>

#include "1784.hpp"

inline static constexpr auto kMethodToTest = &Solution::checkOnesSegment;
inline static constexpr std::string_view kTestCases = R"(
"1001"
false

"110"
true

)";
