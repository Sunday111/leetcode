#include <algorithm>
#include <ranges>

#include "0894_all_possible_full_binary_trees.hpp"
#include "gtest/gtest.h"
#include "leet_code_binary_tree.hpp"
#include "parse_2d_array.hpp"

TEST(t0894_all_possible_full_binary_trees, test_1)
{
    constexpr int n = 7;
    std::string_view expected_str =
        "[[0,0,0,null,null,0,0,null,null,0,0],[0,0,0,null,null,0,0,0,0],[0,0,0,"
        "0,0,0,0],[0,0,0,0,0,null,null,null,null,0,0],[0,0,0,0,0,null,null,0,0]"
        "]";
    auto expected_arrs =
        parse_from_string<std::vector<std::vector<std::optional<int>>>>(
            expected_str);

    auto actual_trees = Solution{}.allPossibleFBT(n);
    auto actual_arrs = std::ranges::to<std::vector>(
        actual_trees |
        std::views::transform(LeetCodeBinaryTree<TreeNode>::ToArray));
    DeleteBinaryTreesWithSharedNodes(std::span{actual_trees});

    std::ranges::sort(expected_arrs);
    std::ranges::sort(actual_arrs);

    ASSERT_EQ(expected_arrs, actual_arrs);
}
TEST(t0894_all_possible_full_binary_trees, test_2)
{
    constexpr int n = 3;
    std::string_view expected_str = "[[0,0,0]]";
    auto expected_arrs =
        parse_from_string<std::vector<std::vector<std::optional<int>>>>(
            expected_str);

    auto actual_trees = Solution{}.allPossibleFBT(n);
    auto actual_arrs = std::ranges::to<std::vector>(
        actual_trees |
        std::views::transform(LeetCodeBinaryTree<TreeNode>::ToArray));
    DeleteBinaryTreesWithSharedNodes(std::span{actual_trees});

    std::ranges::sort(expected_arrs);
    std::ranges::sort(actual_arrs);

    ASSERT_EQ(expected_arrs, actual_arrs);
}
