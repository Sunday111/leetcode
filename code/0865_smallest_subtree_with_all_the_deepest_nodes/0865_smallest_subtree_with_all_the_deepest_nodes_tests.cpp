#include "0865_smallest_subtree_with_all_the_deepest_nodes.hpp"
#include "gtest/gtest.h"
#include "leet_code_binary_tree.hpp"

TEST(t0865_smallest_subtree_with_all_the_deepest_nodes, test_1)
{
    auto original =
        LeetCodeBinaryTree<TreeNode>::FromString("3,5,1,6,2,0,8,null,null,7,4");
    auto expected = LeetCodeBinaryTree<TreeNode>::FromString("2,7,4");
    auto actual = Solution{}.subtreeWithAllDeepest(original.root);
    ASSERT_TRUE(CompareBinaryTrees<TreeNode>(actual, expected.root));
}

TEST(t0865_smallest_subtree_with_all_the_deepest_nodes, test_2)
{
    auto original = LeetCodeBinaryTree<TreeNode>::FromString("1");
    auto expected = LeetCodeBinaryTree<TreeNode>::FromString("1");
    auto actual = Solution{}.subtreeWithAllDeepest(original.root);
    ASSERT_TRUE(CompareBinaryTrees<TreeNode>(actual, expected.root));
}

TEST(t0865_smallest_subtree_with_all_the_deepest_nodes, test_3)
{
    auto original = LeetCodeBinaryTree<TreeNode>::FromString("0,1,3,null,2");
    auto expected = LeetCodeBinaryTree<TreeNode>::FromString("2");
    auto actual = Solution{}.subtreeWithAllDeepest(original.root);
    ASSERT_TRUE(CompareBinaryTrees<TreeNode>(actual, expected.root));
}

TEST(t0865_smallest_subtree_with_all_the_deepest_nodes, test_4)
{
    auto original =
        LeetCodeBinaryTree<TreeNode>::FromString("0,2,1,null,null,3");
    auto expected = LeetCodeBinaryTree<TreeNode>::FromString("3");
    auto actual = Solution{}.subtreeWithAllDeepest(original.root);
    ASSERT_TRUE(CompareBinaryTrees<TreeNode>(actual, expected.root));
}
