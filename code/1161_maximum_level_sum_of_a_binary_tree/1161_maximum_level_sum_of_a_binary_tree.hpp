#include <algorithm>

#include "int_if.hpp"
#include "lc_tree_node.hpp"

class Solution
{
public:
    [[nodiscard]] static int maxLevelSum(TreeNode* root) noexcept
    {
        TreeNode* q[10'001];
        int qb = 0, qe = 0, r = 1, max_s = root->val;
        q[qe++] = root;
        for (int level = 1; qb != qe; ++level)
        {
            int s = 0, e = qe;
            while (qb != e)
            {
                auto node = q[qb++];
                s += node->val;
                q[qe] = node->left, qe += !!q[qe];
                q[qe] = node->right, qe += !!q[qe];
            }

            r = iif(max_s < s, level, r);
            max_s = std::max(max_s, s);
        }

        return r;
    }
};
