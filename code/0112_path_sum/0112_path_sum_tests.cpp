#include "0112_path_sum.hpp"
#include "gtest/gtest.h"
#include "test_utility.hpp"

using Tree = LeetCodeBinaryTree<TreeNode>;

TEST(t0112_path_sum, test_1)
{
    Solution s{};
    auto tree = Tree::FromString("5,4,8,11,null,13,4,7,2,null,null,null,1");
    ASSERT_EQ(s.hasPathSum(tree.root, 22), true);
}

TEST(t0112_path_sum, test_2)
{
    Solution s{};
    auto tree = Tree::FromString("1,2,3");
    ASSERT_EQ(s.hasPathSum(tree.root, 5), false);
}

TEST(t0112_path_sum, test_3)
{
    Solution s{};
    ASSERT_EQ(s.hasPathSum(nullptr, 0), false);
}
