#pragma once

#include <algorithm>
#include <unordered_map>
#include <vector>

struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}  // NOLINT
    TreeNode(int x, TreeNode* left, TreeNode* right)
        : val(x),
          left(left),
          right(right)
    {
    }
};

class Solution
{
public:
    struct NodeInfo
    {
        TreeNode* parent = nullptr;
        int max_sum_left = std::numeric_limits<int>::lowest();
        int max_sum_right = std::numeric_limits<int>::lowest();
    };

    static int maxPathSum(TreeNode* root)
    {
        std::vector<TreeNode*> queue;
        queue.reserve(30'000);

        std::unordered_map<TreeNode*, NodeInfo> nodes_info;
        nodes_info.reserve(60'000);

        auto propagate_sum_upwards = [&](TreeNode* node)
        {
            NodeInfo* node_info = &nodes_info[node];
            while (node_info->parent)
            {
                auto* parent_node_info = &nodes_info[node_info->parent];

                int& dst_sum = node == node_info->parent->left
                                   ? parent_node_info->max_sum_left
                                   : parent_node_info->max_sum_right;

                const int with_branches =
                    node->val + std::max(
                                    std::max(
                                        node_info->max_sum_left,
                                        node_info->max_sum_right),
                                    0);

                if (with_branches > dst_sum) dst_sum = with_branches;

                node = node_info->parent;
                node_info = parent_node_info;
            }
        };

        queue.push_back(root);
        while (!queue.empty())
        {
            auto node = queue.back();
            queue.pop_back();

            if (auto child = node->left)
            {
                nodes_info[child].parent = node;
                queue.push_back(child);
            }

            if (auto child = node->right)
            {
                nodes_info[child].parent = node;
                queue.push_back(child);
            }

            if (!(node->left || node->right))
            {
                propagate_sum_upwards(node);
            }
        }

        int max_sum = std::numeric_limits<int>::lowest();
        auto try_num = [&](int value)
        {
            if (value > max_sum)
            {
                max_sum = value;
            }
        };

        for (auto& [node, node_info] : nodes_info)
        {
            if (node->left)
            {
                try_num(node_info.max_sum_left);
                try_num(node_info.max_sum_left + node->val);
            }

            if (node->right)
            {
                try_num(node_info.max_sum_right);
                try_num(node_info.max_sum_right + node->val);
            }

            if (node->left && node->right)
            {
                try_num(
                    node_info.max_sum_left + node_info.max_sum_right +
                    node->val);
            }

            try_num(node->val);
        }

        return max_sum;
    }
};
