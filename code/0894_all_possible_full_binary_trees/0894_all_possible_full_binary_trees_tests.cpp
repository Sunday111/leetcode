#include <algorithm>
#include <ranges>

#include "0894_all_possible_full_binary_trees.hpp"
#include "gtest/gtest.h"
#include "leet_code_binary_tree.hpp"
#include "test_cases_helpers.hpp"

static const auto kCases = parse_test_cases_with_types<
    std::tuple<int>,
    std::vector<std::vector<std::optional<int>>>>(R"cases(
7 [[0,0,0,null,null,0,0,null,null,0,0],[0,0,0,null,null,0,0,0,0],[0,0,0,0,0,0,0],[0,0,0,0,0,null,null,null,null,0,0],[0,0,0,0,0,null,null,0,0]]
3 [[0,0,0]]
)cases");

class t0894_all_possible_full_binary_trees
    : public ::testing::TestWithParam<size_t>
{
};
TEST_P(t0894_all_possible_full_binary_trees, Test)
{
    auto [inputs, expected] = kCases.at(GetParam());
    auto trees = Solution{}.allPossibleFBT(std::get<0>(inputs));
    auto actual = std::ranges::to<std::vector>(
        trees | std::views::transform(LeetCodeBinaryTree<TreeNode>::ToArray));
    DeleteBinaryTreesWithSharedNodes(std::span{trees});
    std::ranges::sort(expected);
    std::ranges::sort(actual);
    ASSERT_EQ(expected, actual);
}
INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0894_all_possible_full_binary_trees,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });
