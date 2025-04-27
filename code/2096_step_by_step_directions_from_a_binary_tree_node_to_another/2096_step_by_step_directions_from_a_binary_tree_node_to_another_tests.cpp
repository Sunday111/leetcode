#include "2096_step_by_step_directions_from_a_binary_tree_node_to_another.hpp"
#include "gtest/gtest.h"
#include "test_utility.hpp"

using Tree = LeetCodeBinaryTree<TreeNode>;

TEST(t2096_step_by_step_directions_from_a_binary_tree_node_to_another, test_1)
{
    auto tree = Tree::FromString("5,1,2,3,null,6,4");
    constexpr int start_value = 3;
    constexpr int dest_value = 6;
    constexpr std::string_view expected = "UURL";

    Solution s{};
    ASSERT_EQ(s.getDirections(tree.root, start_value, dest_value), expected);
}
