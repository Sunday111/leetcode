#pragma once

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

    TreeNode* lowestCommonAncestor(TreeNode* n, TreeNode* pn, TreeNode* qn)
    {
        const int p = pn->val, q = qn->val;
        while (true)
        {
            if (p < n->val && q < n->val)
            {
                n = n->left;
            }
            else if (p > n->val && q > n->val)
            {
                n = n->right;
            }
            else
            {
                break;
            }
        }

        return n;
    }
};
