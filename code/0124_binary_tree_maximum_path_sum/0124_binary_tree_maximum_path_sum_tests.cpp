#include <cassert>

#include "0124_binary_tree_maximum_path_sum.hpp"
#include "gtest/gtest.h"
#include "leet_code_binary_tree.hpp"

using Tree = LeetCodeBinaryTree<TreeNode>;

TEST(t0124_binary_tree_maximum_path_sum, test_1)
{
    Solution s{};

    auto tree = Tree::FromString("1,2,3");
    ASSERT_EQ(s.maxPathSum(tree.root), 6);
}

TEST(t0124_binary_tree_maximum_path_sum, test_2)
{
    Solution s{};

    auto tree = Tree::FromString("-10,9,20,null,null,15,7");
    ASSERT_EQ(s.maxPathSum(tree.root), 42);
}

TEST(t0124_binary_tree_maximum_path_sum, test_3)
{
    Solution s{};

    auto tree = Tree::FromString("-2,-1");
    ASSERT_EQ(s.maxPathSum(tree.root), -1);
}
