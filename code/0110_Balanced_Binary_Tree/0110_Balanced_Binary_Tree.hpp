#pragma once

#include <algorithm>
#include <cmath>

#include "lc_tree_node.hpp"

class Solution
{
public:
    static constexpr int getTreeHeight(TreeNode* n)
    {
        if (!n) return 0;
        return 1 + std::max(getTreeHeight(n->left), getTreeHeight(n->right));
    }

    static constexpr bool isBalanced(TreeNode* root)
    {
        if (!root) return true;
        int l = getTreeHeight(root->left), r = getTreeHeight(root->right);
        return (
            (2 > std::abs(l - r)) && isBalanced(root->left) &&
            isBalanced(root->right));
    }
};
