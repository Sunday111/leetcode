#include "1123_lowest_common_ancestor_of_deepest_leaves.hpp"
#include "gtest/gtest.h"
#include "leet_code_binary_tree.hpp"

TEST(t1123_lowest_common_ancestor_of_deepest_leaves, test_1)
{
    auto original =
        LeetCodeBinaryTree<TreeNode>::FromString("3,5,1,6,2,0,8,null,null,7,4");
    auto expected = LeetCodeBinaryTree<TreeNode>::FromString("2,7,4");
    auto actual = Solution{}.lcaDeepestLeaves(original.root);
    ASSERT_TRUE(CompareBinaryTrees<TreeNode>(actual, expected.root));
}

TEST(t1123_lowest_common_ancestor_of_deepest_leaves, test_2)
{
    auto original =
        LeetCodeBinaryTree<TreeNode>::FromString("3,5,1,6,2,0,8,null,null,7,4");
    auto expected = LeetCodeBinaryTree<TreeNode>::FromString("2,7,4");
    auto actual = Solution{}.lcaDeepestLeaves(original.root);
    ASSERT_TRUE(CompareBinaryTrees<TreeNode>(actual, expected.root));
}

TEST(t1123_lowest_common_ancestor_of_deepest_leaves, test_3)
{
    auto original =
        LeetCodeBinaryTree<TreeNode>::FromString("3,5,1,6,2,0,8,null,null,7,4");
    auto expected = LeetCodeBinaryTree<TreeNode>::FromString("2,7,4");
    auto actual = Solution{}.lcaDeepestLeaves(original.root);
    ASSERT_TRUE(CompareBinaryTrees<TreeNode>(actual, expected.root));
}

TEST(t1123_lowest_common_ancestor_of_deepest_leaves, test_4)
{
    auto original =
        LeetCodeBinaryTree<TreeNode>::FromString("3,5,1,6,2,0,8,null,null,7,4");
    auto expected = LeetCodeBinaryTree<TreeNode>::FromString("2,7,4");
    auto actual = Solution{}.lcaDeepestLeaves(original.root);
    ASSERT_TRUE(CompareBinaryTrees<TreeNode>(actual, expected.root));
}
