#include "0110_Balanced_Binary_Tree.hpp"
#include "gtest/gtest.h"
#include "leet_code_binary_tree.hpp"

using Tree = LeetCodeBinaryTree<TreeNode>;

TEST(t0110_Balanced_Binary_Tree, test_1)
{
    auto tree = Tree::FromString("3,9,20,null,null,15,7");
    ASSERT_EQ(Solution{}.isBalanced(tree.root), true);
}

TEST(t0110_Balanced_Binary_Tree, test_2)
{
    auto tree = Tree::FromString("1,2,2,3,3,null,null,4,4");
    ASSERT_EQ(Solution{}.isBalanced(tree.root), false);
}
