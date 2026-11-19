#include "0110_Balanced_Binary_Tree.hpp"
#include "gtest/gtest.h"
#include "leet_code_binary_tree.hpp"
#include "test_cases_helpers.hpp"

static const auto kCases =
    parse_test_cases_with_types<std::tuple<LeetCodeBinaryTree<TreeNode>>, bool>(
        R"cases(
[3,9,20,null,null,15,7] true
[1,2,2,3,3,null,null,4,4] false
)cases");

class t0110_Balanced_Binary_Tree : public ::testing::TestWithParam<size_t>
{
};
TEST_P(t0110_Balanced_Binary_Tree, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto& [tree] = inputs;
    ASSERT_EQ(expected, cast<bool>(Solution{}.isBalanced(tree.root)));
}
INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0110_Balanced_Binary_Tree,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
