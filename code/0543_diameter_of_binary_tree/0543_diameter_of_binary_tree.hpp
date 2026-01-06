#include <algorithm>

#include "lc_tree_node.hpp"

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
