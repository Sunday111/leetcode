#include "0437_path_sum_3.hpp"
#include "gtest/gtest.h"
#include "leet_code_binary_tree.hpp"

using Tree = LeetCodeBinaryTree<TreeNode>;

TEST(t0437_path_sum_3, test_1)
{
    auto tree = Tree::FromString("10,5,-3,3,2,null,11,3,-2,null,1");
    constexpr int target_sum = 8;
    constexpr int expected = 3;
    Solution s{};
    ASSERT_EQ(s.pathSum(tree.root, target_sum), expected);
}

TEST(t0437_path_sum_3, test_2)
{
    auto tree = Tree::FromString("5,4,8,11,null,13,4,7,2,null,null,5,1");
    constexpr int target_sum = 22;
    constexpr int expected = 3;
    Solution s{};
    ASSERT_EQ(s.pathSum(tree.root, target_sum), expected);
}
