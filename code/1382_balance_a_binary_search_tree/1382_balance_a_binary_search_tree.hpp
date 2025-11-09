#pragma once

#include <bit>
#include <utility>

#include "force_inline.hpp"

namespace dsw_impl
{

template <typename Node>
FORCE_INLINE constexpr unsigned bstToVine(Node* grand) noexcept
{
    unsigned count = 0;
    auto tmp = grand->right;

    while (tmp)
    {
        if (tmp->left)
        {
            auto old = std::exchange(tmp, tmp->left);
            old->left = std::exchange(tmp->right, old);
            grand->right = tmp;
        }
        else
        {
            count++;
            grand = std::exchange(tmp, tmp->right);
        }
    }

    return count;
}

template <typename Node>
FORCE_INLINE constexpr void rotate(Node* grand, unsigned m) noexcept
{
    for (auto tmp = grand->right; m--;)
    {
        auto old = std::exchange(tmp, tmp->right);
        grand->right = tmp;
        old->right = tmp->left;
        tmp->left = old;
        grand = std::exchange(tmp, tmp->right);
    }
}

template <typename Node>
FORCE_INLINE constexpr auto balanceBST(Node* root) noexcept
{
    Node dummy{0};
    dummy.right = root;
    unsigned n = bstToVine(&dummy);
    unsigned m = (1u << (std::bit_width(n + 1u) - 1)) - 1u;
    rotate(&dummy, n - m);
    while (m >>= 1) rotate(&dummy, m);
    return dummy.right;
}
}  // namespace dsw_impl

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
