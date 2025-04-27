#include "0257_binary_tree_paths.hpp"
#include "gtest/gtest.h"
#include "test_utility.hpp"

using Tree = LeetCodeBinaryTree<TreeNode>;

TEST(t0257_binary_tree_paths, test_1)
{
    auto tree = Tree::FromString("1,2,3,null,5");
    std::vector<std::string> expected{"1->2->5", "1->3"};
    Solution s{};
    ASSERT_EQ(s.binaryTreePaths(tree.root), expected);
}
