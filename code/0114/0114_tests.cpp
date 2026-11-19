#include <array>
#include <cstddef>
#include <string_view>
#include <vector>

#include "0114.hpp"
#include "leet_code_binary_tree.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static const auto kCases =
    parse_test_cases_with_types<std::tuple<std::string>, std::vector<size_t>>(
        R"cases(
"null" []
"0" [0]
"1,2,5,3,4,null,6" [0,1,3,4,2,5]
"1,2" [0,1]
"1,2,null,3" [0,1,2]
"1,null,2,null,3" [0,1,2]
"1,null,2,3" [0,1,2]
"1,1,1,1,1" [0,1,3,4,2]
)cases");

using t0114 = SolutionTests<Solution>;
TEST_P(t0114, Test)
{
    run(kCases,
        [](auto& solution, auto& inputs, auto& expected)
        {
            auto tree =
                LeetCodeBinaryTree<TreeNode>::FromString(std::get<0>(inputs));
            solution.flatten(tree.root);
            auto* node = tree.root;
            for (auto index : expected)
            {
                ASSERT_EQ(node, &tree.nodes[index]);
                ASSERT_EQ(node->left, nullptr);
                node = node->right;
            }
            ASSERT_EQ(node, nullptr);
        });
}
INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0114,
    t0114::parameters(kCases.size()),
    t0114::name);
