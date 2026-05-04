#pragma once

#include "0061.hpp"
#include "test_cases_helpers.hpp"

inline static const auto kCases = parse_test_cases_with_types<
    std::tuple<std::vector<int>, int>,
    std::vector<int>>(R"(
[1,2,3,4,5]
2
[4,5,1,2,3]

[0,1,2]
4
[2,0,1]
)");
