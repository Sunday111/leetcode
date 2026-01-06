#pragma once

#include "dsw.hpp"
#include "lc_tree_node.hpp"

class Solution
{
public:
    static constexpr TreeNode* balanceBST(TreeNode* root) noexcept
    {
        return dsw_impl::balanceBST(root);
    }
};
