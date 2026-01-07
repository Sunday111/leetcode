#include <algorithm>

#include "integral_aliases.hpp"
#include "lc_tree_node.hpp"

class Solution
{
public:
    int acc(TreeNode* root) noexcept
    {
        if (!root) return 0;
        return root->val += acc(root->left) + acc(root->right);
    }

    int total = 0;

    i64 dfs(TreeNode* node) noexcept
    {
        if (!node) return 0;
        return std::max(
            i64{total - node->val} * i64{node->val},
            std::max(dfs(node->left), dfs(node->right)));
    }

    auto maxProduct(TreeNode* root)
    {
        total = acc(root);
        return dfs(root) % 1'000'000'007;
    }
};
