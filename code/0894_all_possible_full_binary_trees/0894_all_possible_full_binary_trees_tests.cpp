#include <algorithm>
#include <ranges>

#include "0894_all_possible_full_binary_trees.hpp"
#include "leet_code_binary_tree.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static const auto kCases = parse_test_cases_with_types<
    std::tuple<int>,
    std::vector<std::vector<std::optional<int>>>>(R"cases(
7 [[0,0,0,null,null,0,0,null,null,0,0],[0,0,0,null,null,0,0,0,0],[0,0,0,0,0,0,0],[0,0,0,0,0,null,null,null,null,0,0],[0,0,0,0,0,null,null,0,0]]
3 [[0,0,0]]
)cases");

using t0894_all_possible_full_binary_trees = SolutionTests<Solution>;
TEST_P(t0894_all_possible_full_binary_trees, Test)
{
    run(kCases,
        [](auto& solution, auto& inputs, auto& expected)
        {
            auto trees = solution.allPossibleFBT(std::get<0>(inputs));
            auto actual = std::ranges::to<std::vector>(
                trees |
                std::views::transform(LeetCodeBinaryTree<TreeNode>::ToArray));
            DeleteBinaryTreesWithSharedNodes(std::span{trees});
            std::ranges::sort(expected);
            std::ranges::sort(actual);
            ASSERT_EQ(expected, actual);
        });
}
INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0894_all_possible_full_binary_trees,
    t0894_all_possible_full_binary_trees::parameters(kCases.size()),
    t0894_all_possible_full_binary_trees::name);
