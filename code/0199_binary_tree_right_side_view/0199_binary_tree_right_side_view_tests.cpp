#include "0199_binary_tree_right_side_view.hpp"
#include "gtest/gtest.h"
#include "leet_code_binary_tree.hpp"

using Tree = LeetCodeBinaryTree<TreeNode>;

TEST(t0199_binary_tree_right_side_view, test_1)
{
    Solution s{};
    auto tree = Tree::FromString("1,2,3,4,null,null,null,5");
    std::vector expected{1, 3, 4, 5};
    ASSERT_EQ(s.rightSideView(tree.root), expected);
}
