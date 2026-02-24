#include "1022_sum_of_root_to_leaf_binary_numbers.hpp"
#include "gtest/gtest.h"
#include "leet_code_binary_tree.hpp"

TEST(t1022_sum_of_root_to_leaf_binary_numbers, test_1)
{
    auto tree = LeetCodeBinaryTree<TreeNode>::FromString("1,0,1,0,1,0,1");
    ASSERT_EQ(Solution{}.sumRootToLeaf(tree.root), 22);
}
