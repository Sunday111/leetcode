#include <cstdint>

#include "lc_tree_node.hpp"

class Solution
{
public:
    using u32 = uint32_t;
    [[nodiscard]] static constexpr u32 sumRootToLeaf(
        TreeNode* x,
        u32 p = 0) noexcept
    {
        if (!x) return 0;
        p = (p << 1) | (x->val & 1);
        u32 r = (p & -u32{!x->left && !x->right});
        r += sumRootToLeaf(x->left, p);
        r += sumRootToLeaf(x->right, p);
        return r;
    }
};
