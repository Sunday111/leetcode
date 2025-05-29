#include "0988_smallest_string_starting_from_leaf.hpp"
#include "gtest/gtest.h"
#include "leet_code_binary_tree.hpp"

using Tree = LeetCodeBinaryTree<TreeNode>;

TEST(t0988_smallest_string_starting_from_leaf, test_1)
{
    Solution s{};
    auto tree = Tree::FromString("0,1,2,3,4,3,4");
    ASSERT_EQ(s.smallestFromLeaf(tree.root), "dba");
}
TEST(t0988_smallest_string_starting_from_leaf, test_2)
{
    Solution s{};
    auto tree = Tree::FromString("25,1,3,1,3,0,2");
    ASSERT_EQ(s.smallestFromLeaf(tree.root), "adz");
}
TEST(t0988_smallest_string_starting_from_leaf, test_3)
{
    Solution s{};
    auto tree = Tree::FromString("25,0,null,1,null,0,0,1,null,null,null,0");
    ASSERT_EQ(s.smallestFromLeaf(tree.root), "ababaz");
}
