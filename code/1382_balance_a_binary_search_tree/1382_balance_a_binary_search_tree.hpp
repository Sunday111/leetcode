#pragma once

#include "dsw.hpp"

struct TreeNode
{
    int val{};
    TreeNode* left{};
    TreeNode* right{};
};

class Solution
{
public:
    static constexpr TreeNode* balanceBST(TreeNode* root) noexcept
    {
        return dsw_impl::balanceBST(root);
    }
};
