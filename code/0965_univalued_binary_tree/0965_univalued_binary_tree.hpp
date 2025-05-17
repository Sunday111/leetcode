#pragma once

struct TreeNode
{
    int val;
    TreeNode* left{nullptr};
    TreeNode* right{nullptr};
    explicit TreeNode(int x) : val(x) {}
};

class Solution
{
public:
    int v;
    bool isUnivalTreeR(TreeNode* root)
    {
        if (root)
        {
            if (root->val != v) return false;
            if (!isUnivalTreeR(root->left)) return false;
            if (!isUnivalTreeR(root->right)) return false;
        }

        return true;
    }
    bool isUnivalTree(TreeNode* root)
    {
        v = root->val;
        return isUnivalTreeR(root);
    }
};
