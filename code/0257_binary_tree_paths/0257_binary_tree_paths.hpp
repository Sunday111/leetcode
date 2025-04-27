#pragma once

#include <format>
#include <string>
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
    std::vector<std::string> paths;
    std::string path;
    void binaryTreePathsR(TreeNode* node)
    {
        if (node)
        {
            size_t prev_len = path.size();
            std::format_to(std::back_inserter(path), "->{}", node->val);
            if (node->left || node->right)
            {
                binaryTreePathsR(node->left);
                binaryTreePathsR(node->right);
            }
            else
            {
                paths.push_back(path);
            }

            path.resize(prev_len);
        }
    }

    std::vector<std::string> binaryTreePaths(TreeNode* root)
    {
        paths.clear();
        path.clear();

        if (root)
        {
            std::format_to(std::back_inserter(path), "{}", root->val);
            if (root->left || root->right)
            {
                binaryTreePathsR(root->left);
                binaryTreePathsR(root->right);
            }
            else
            {
                paths.push_back(path);
            }
        }

        return paths;
    }
};
