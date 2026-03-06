#pragma once

#include "1557_minimum_number_of_vertices_to_reach_all_nodes.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest =
    &Solution::findSmallestSetOfVertices;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
6
[[0,1],[0,2],[2,5],[3,4],[4,2]]
[0,3]

5
[[0,1],[2,1],[3,1],[1,4],[2,4]]
[0,2,3]

)");
