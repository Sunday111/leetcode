#pragma once

#include <algorithm>

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
    int max_d = 0;

    int dfs(TreeNode* root)
    {
        if (!root) return 0;

        int l = dfs(root->left);
        int r = dfs(root->right);
        int lp = root->left ? 1 + l : 0;
        int rp = root->right ? 1 + r : 0;
        if (int k = lp + rp; k > max_d) max_d = k;
        return std::max(lp, rp);
    }

    int diameterOfBinaryTree(TreeNode* root)
    {
        max_d = 0;
        dfs(root);
        return max_d;
    }
};
