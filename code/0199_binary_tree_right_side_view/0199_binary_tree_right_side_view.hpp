#pragma once

#include <vector>

struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    explicit TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
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
    inline static constexpr size_t kMaxNodes = 100;

    std::vector<int> rightSideView(TreeNode* root)
    {
        std::vector<int> r;
        r.reserve(kMaxNodes);

        std::vector<TreeNode*> q;
        q.reserve(kMaxNodes);
        if (root) q.push_back(root);

        while (!q.empty())
        {
            r.push_back(q.back()->val);
            size_t k = q.size();

            for (size_t i = 0; i != k; ++i)
            {
                auto* node = q[i];
                if (node->left) q.push_back(node->left);
                if (node->right) q.push_back(node->right);
            }

            q.erase(q.begin(), std::next(q.begin(), static_cast<ssize_t>(k)));
        }

        return r;
    }
};
