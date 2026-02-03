#include <vector>

#include "lc_tree_node.hpp"

class Solution
{
public:
    [[nodiscard]] static constexpr TreeNode* bstFromPreorder(
        const std::vector<int>& p) noexcept
    {
        auto dfs = [&, i = size_t{0}](auto& f, int lim) mutable -> TreeNode*
        {
            if (i == p.size() || p[i] >= lim) return nullptr;
            auto x = new TreeNode(p[i++]);  // NOLINT
            x->left = f(f, x->val);
            x->right = f(f, lim);
            return x;
        };

        return dfs(dfs, std::numeric_limits<int>::max());
    }
};
