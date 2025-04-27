#pragma once

#include <bitset>
#include <cassert>
#include <optional>

//   Definition for a binary tree node.
struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    explicit TreeNode(int x = 0, TreeNode* l = nullptr, TreeNode* r = nullptr)
        : val(x),
          left(l),
          right(r)
    {
    }
};
class Solution
{
public:
    std::optional<TreeNode*> result_;
    TreeNode* p_;
    TreeNode* q_;

    template <bool find_p, bool find_q>
    std::bitset<2> LCA(TreeNode* node)
    {
        auto visit_child = [this](std::bitset<2>& r, TreeNode* child)
        {
            switch (r.to_ulong())
            {
            case 0b00:
                r |= LCA<find_p, find_q>(child);
                break;
            case 0b01:
                r |= LCA<false, find_q>(child);
                break;
            case 0b10:
                r |= LCA<find_p, false>(child);
                break;
            }
        };

        std::bitset<2> r;
        if constexpr (find_p || find_q)
        {
            if (node)
            {
                if constexpr (find_p)
                {
                    if (node == p_) r[0] = true;
                }

                if constexpr (find_q)
                {
                    if (node == q_) r[1] = true;
                }

                visit_child(r, node->left);
                visit_child(r, node->right);

                if (r.all() && !result_) result_ = node;
            }
        }

        return r;
    }

    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
    {
        result_ = std::nullopt;
        p_ = p;
        q_ = q;
        LCA<true, true>(root);
        return result_.value_or(nullptr);
    }
};
