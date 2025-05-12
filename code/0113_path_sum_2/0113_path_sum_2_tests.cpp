#include "0113_path_sum_2.hpp"
#include "gtest/gtest.h"
#include "leet_code_binary_tree.hpp"

using Tree = LeetCodeBinaryTree<TreeNode>;

TEST(t0113_path_sum_2, test_1)
{
    auto tree = Tree::FromString("5,4,8,11,null,13,4,7,2,null,null,5,1");
    constexpr int target_sum = 22;
    std::vector<std::vector<int>> expected{
        {5, 4, 11, 2},
        {5, 8, 4, 5},
    };
    Solution s{};
    ASSERT_EQ(s.binaryTreePaths(tree.root, target_sum), expected);
}
