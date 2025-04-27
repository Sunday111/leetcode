#pragma once

#include <vector>

// Definition for a binary tree node.
struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    explicit TreeNode(
        int x,
        TreeNode* left = nullptr,
        TreeNode* right = nullptr)
        : val(x),
          left(left),
          right(right)
    {
    }
};

class Solution
{
public:
    std::vector<std::vector<int>> paths;

    std::vector<int> path;
    int sum = 0;
    int target = 0;

    void binaryTreePathsR(TreeNode* node)
    {
        if (node)
        {
            path.push_back(node->val);
            sum += node->val;

            if (node->left || node->right)
            {
                binaryTreePathsR(node->left);
                binaryTreePathsR(node->right);
            }
            else if (sum == target)
            {
                paths.push_back(path);
            }

            sum -= path.back();
            path.pop_back();
        }
    }

    std::vector<std::vector<int>> binaryTreePaths(
        TreeNode* root,
        int target_sum)
    {
        paths.clear();
        path.clear();
        sum = 0;
        target = target_sum;
        binaryTreePathsR(root);
        return paths;
    }
};
