#include "0114_test_cases.hpp"
#include "gtest/gtest.h"
#include "leet_code_binary_tree.hpp"

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
