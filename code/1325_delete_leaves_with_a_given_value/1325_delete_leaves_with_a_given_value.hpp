#pragma once

struct TreeNode
{
    TreeNode *left, *right;
    int val;
};

class Solution
{
public:
    [[nodiscard]] static constexpr TreeNode* removeLeafNodes(
        TreeNode* root,
        int t) noexcept
    {
        if (root)
        {
            root->left = removeLeafNodes(root->left, t);
            root->right = removeLeafNodes(root->right, t);
            if (!(root->left || root->right) && root->val == t)
            {
                root = nullptr;
            }
        }
        return root;
    }
};
