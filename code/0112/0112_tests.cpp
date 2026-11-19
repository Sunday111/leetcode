#include "0112.hpp"
#include "leet_code_binary_tree.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static const auto kCases = parse_test_cases_with_types<
    std::tuple<LeetCodeBinaryTree<TreeNode>, int>,
    bool>(R"cases(
[5,4,8,11,null,13,4,7,2,null,null,null,1] 22 true
[1,2,3] 5 false
[null] 0 false
)cases");

using t0112 = SolutionTests<Solution>;
TEST_P(t0112, Test)
{
    run(kCases,
        [](auto& solution, auto& inputs, auto& expected)
        {
            auto& [tree, sum] = inputs;
            ASSERT_EQ(expected, solution.hasPathSum(tree.root, sum));
        });
}
INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0112,
    t0112::parameters(kCases.size()),
    t0112::name);
