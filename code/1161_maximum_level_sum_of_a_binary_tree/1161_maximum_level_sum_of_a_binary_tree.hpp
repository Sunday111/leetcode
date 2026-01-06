#include "lc_tree_node.hpp"

class Solution
{
public:
    [[nodiscard]] static int maxLevelSum(TreeNode* root) noexcept
    {
        TreeNode* q[10'001];
        int qb = 0, qe = 0;
        int best_level = 1, best_sum = root->val;
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

            if (s > best_sum)
            {
                best_sum = s;
                best_level = level;
            }
        }

        return best_level;
    }
};
