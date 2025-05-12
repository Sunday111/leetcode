#include "0543_diameter_of_binary_tree.hpp"
#include "gtest/gtest.h"
#include "leet_code_binary_tree.hpp"

using Tree = LeetCodeBinaryTree<TreeNode>;

TEST(t0543_diameter_of_binary_tree, test_1)
{
    Solution s{};
    auto tree = Tree::FromString("1,2,3,4,5");
    ASSERT_EQ(s.diameterOfBinaryTree(tree.root), 3);
}

TEST(t0543_diameter_of_binary_tree, test_2)
{
    Solution s{};
    auto tree = Tree::FromString("1,2");
    ASSERT_EQ(s.diameterOfBinaryTree(tree.root), 1);
}
