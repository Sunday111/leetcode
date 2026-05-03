#pragma once

#include "0048.hpp"
#include "test_cases_helpers.hpp"

inline static const auto kCases = parse_test_cases_with_types<
    std::vector<std::vector<int>>,
    std::vector<std::vector<int>>>(
    R"(
[[1,2,3],[4,5,6],[7,8,9]]                           [[7,4,1],[8,5,2],[9,6,3]]
[[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]]    [[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]]
)");
