#include "1008_construct_binary_search_tree_from_preorder_traversal.hpp"
#include "gtest/gtest.h"
#include "leet_code_binary_tree.hpp"

using Tree = LeetCodeBinaryTree<TreeNode>;

TEST(t1008_construct_binary_search_tree_from_preorder_traversal, test_1)
{
    std::vector preorder{8, 5, 1, 7, 10, 12};
    auto expected = Tree::FromString("8,5,10,1,7,null,12");
    auto actual = Solution{}.bstFromPreorder(preorder);
    ASSERT_TRUE(CompareBinaryTrees(expected.root, actual));
    DeleteBinaryTree(actual);
}
