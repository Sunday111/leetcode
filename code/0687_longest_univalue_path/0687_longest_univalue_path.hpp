#include <algorithm>

#include "lc_tree_node.hpp"

class Solution
{
public:
    int max_len = 0;

    int dfs(TreeNode* n)
    {
        if (!n) return 0;

        int left_path = 0;
        int left = dfs(n->left);
        if (n->left && n->left->val == n->val) left_path = left + 1;

        int right_path = 0;
        int right = dfs(n->right);
        if (n->right && n->right->val == n->val) right_path = right + 1;

        max_len = std::max(max_len, left_path + right_path);

        return std::max(left_path, right_path);
    }

    int longestUnivaluePath(TreeNode* root)
    {
        dfs(root);
        return max_len;
    }
};
