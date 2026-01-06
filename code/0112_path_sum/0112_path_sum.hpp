#pragma once

#include "lc_tree_node.hpp"

class Solution
{
public:
    static constexpr bool hasPathSum(const TreeNode* root, int targetSum)
    {
        if (!root) return false;

        targetSum -= root->val;
        if (root->left || root->right)
        {
            return (root->left && hasPathSum(root->left, targetSum)) ||
                   (root->right && hasPathSum(root->right, targetSum));
        }

        return targetSum == 0;
    }
};
