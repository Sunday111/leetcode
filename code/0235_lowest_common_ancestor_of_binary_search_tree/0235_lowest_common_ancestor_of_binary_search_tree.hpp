#include <cassert>
#include <optional>

#include "lc_tree_node.hpp"

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
