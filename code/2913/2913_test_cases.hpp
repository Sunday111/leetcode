#pragma once

#include "2913.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto k_method_to_test = &Solution::sumCounts;
inline static const auto k_cases = parse_test_cases<k_method_to_test>(R"(
[1] 1
[1,1] 3
[1,2,1] 15
[2,2] 3
[7,7,7,7,7] 15
[1,2,3,4] 50
[1,2,1,2,1] 45
[1,1,2,2,1] 39
[1,2,3,1,2,3] 116
[100,1,100] 15
[1,2,3,4,5,1] 185
)");
