#include <utility>

#include "lc_tree_node.hpp"

class Solution
{
public:
    [[nodiscard]] static constexpr std::pair<int, TreeNode*> dfs(
        TreeNode* node,
        int d = 0) noexcept
    {
        if (!node) return {d, nullptr};
        ++d;
        auto [ld, ln] = dfs(node->left, d);
        auto [rd, rn] = dfs(node->right, d);
        if (ld == rd) return {ld, node};
        if (ld > rd) return {ld, ln};
        return {rd, rn};
    }

    [[nodiscard]] static constexpr TreeNode* lcaDeepestLeaves(
        TreeNode* root) noexcept
    {
        return dfs(root).second;
    }
};
