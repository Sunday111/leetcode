#include <algorithm>
#include <cmath>

#include "lc_tree_node.hpp"

class Solution
{
public:
    struct Result
    {
        int h = 0;
        [[nodiscard]] constexpr operator bool() const noexcept  // NOLINT
        {
            return h != -1;
        }
    };

    [[nodiscard]] static constexpr Result isBalanced(TreeNode* n) noexcept
    {
        if (!n) return {};
        auto l = isBalanced(n->left);
        if (!l) return l;
        auto r = isBalanced(n->right);
        bool balanced = r && (std::abs(l.h - r.h) < 2);
        return {balanced ? std::max(l.h, r.h) + 1 : -1};
    }
};
