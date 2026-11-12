#include <array>
#include <cstddef>
#include <string_view>
#include <vector>

#include "0114.hpp"
#include "gtest/gtest.h"
#include "leet_code_binary_tree.hpp"

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

class t0114 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t0114, Test)
{
    const auto& [input, expected_node_indices] = kCases[GetParam()];
    auto tree = LeetCodeBinaryTree<TreeNode>::FromString(input);
    Solution{}.flatten(tree.root);

    auto node = tree.root;
    for (auto index : expected_node_indices)
    {
        ASSERT_EQ(node, &tree.nodes[index]);
        ASSERT_EQ(node->left, nullptr);
        node = node->right;
    }
    ASSERT_EQ(node, nullptr);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0114,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
