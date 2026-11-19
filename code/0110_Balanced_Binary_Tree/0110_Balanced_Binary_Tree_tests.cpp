#include "0110_Balanced_Binary_Tree.hpp"
#include "leet_code_binary_tree.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static const auto kCases =
    parse_test_cases_with_types<std::tuple<LeetCodeBinaryTree<TreeNode>>, bool>(
        R"cases(
[3,9,20,null,null,15,7] true
[1,2,2,3,3,null,null,4,4] false
)cases");

using t0110_Balanced_Binary_Tree = SolutionTests<Solution>;
TEST_P(t0110_Balanced_Binary_Tree, Test)
{
    run(kCases,
        [](auto& solution, auto& inputs, auto& expected)
        {
            auto& [tree] = inputs;
            ASSERT_EQ(expected, cast<bool>(solution.isBalanced(tree.root)));
        });
}
INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0110_Balanced_Binary_Tree,
    t0110_Balanced_Binary_Tree::parameters(kCases.size()),
    t0110_Balanced_Binary_Tree::name);
