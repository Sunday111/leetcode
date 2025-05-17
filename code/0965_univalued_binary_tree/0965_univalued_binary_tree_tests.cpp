#include "0965_univalued_binary_tree.hpp"
#include "gtest/gtest.h"
#include "leet_code_binary_tree.hpp"

using Tree = LeetCodeBinaryTree<TreeNode>;

TEST(t0965_univalued_binary_tree, test_1)
{
    auto tree = Tree::FromString("1,1,1,1,1,null,1");
    Solution s{};
    EXPECT_EQ(s.isUnivalTree(tree.root), true);
}

TEST(t0965_univalued_binary_tree, test_2)
{
    auto tree = Tree::FromString("1,100");
    Solution s{};
    EXPECT_EQ(s.isUnivalTree(tree.root), false);
}
