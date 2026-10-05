#pragma once

#include <array>
#include <cstddef>
#include <string_view>
#include <vector>

#include "0114.hpp"

struct FlattenTestCase
{
    std::string_view input;
    std::vector<size_t> expected_node_indices;
};

inline const std::array kCases{
    FlattenTestCase{"null", {}},
    FlattenTestCase{"0", {0}},
    FlattenTestCase{"1,2,5,3,4,null,6", {0, 1, 3, 4, 2, 5}},
    FlattenTestCase{"1,2", {0, 1}},
    FlattenTestCase{"1,2,null,3", {0, 1, 2}},
    FlattenTestCase{"1,null,2,null,3", {0, 1, 2}},
    FlattenTestCase{"1,null,2,3", {0, 1, 2}},
    FlattenTestCase{"1,1,1,1,1", {0, 1, 3, 4, 2}},
};
