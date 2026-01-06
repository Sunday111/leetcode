#include <unordered_map>

#include "lc_tree_node.hpp"

class Solution
{
public:
    int64_t target_sum{};
    int64_t current_sum{};
    int count{};
    std::unordered_map<int64_t, int> sum_to_frequency;

    void pathSum(TreeNode* node)
    {
        if (node)
        {
            current_sum += node->val;
            if (auto it = sum_to_frequency.find(current_sum - target_sum);
                it != sum_to_frequency.end())
            {
                count += it->second;
            }

            sum_to_frequency[current_sum]++;

            pathSum(node->left);
            pathSum(node->right);

            sum_to_frequency[current_sum]--;
            current_sum -= node->val;
        }
    }

    int pathSum(TreeNode* root, int in_target_sum)
    {
        target_sum = in_target_sum;
        current_sum = 0;
        count = 0;
        sum_to_frequency.clear();
        sum_to_frequency[0]++;
        pathSum(root);
        return count;
    }
};
