#include "0687_longest_univalue_path.hpp"
#include "gtest/gtest.h"
#include "test_utility.hpp"

using Tree = LeetCodeBinaryTree<TreeNode>;

TEST(t0687_longest_univalue_path, test_1)
{
    auto tree = Tree::FromString("5,4,5,1,1,null,5");
    constexpr int expected = 2;
    Solution s{};
    ASSERT_EQ(s.longestUnivaluePath(tree.root), expected);
}

TEST(t0687_longest_univalue_path, test_2)
{
    auto tree = Tree::FromString("1,null,1,1,1,1,1,1");
    constexpr int expected = 4;
    Solution s{};
    ASSERT_EQ(s.longestUnivaluePath(tree.root), expected);
}
