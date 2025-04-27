#pragma once

#include <span>
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
    static bool find_path(TreeNode* from, int to, std::vector<TreeNode*>& path)
    {
        if (from)
        {
            path.push_back(from);
            if (from->val == to)
            {
                return true;
            }

            if (!(find_path(from->left, to, path) ||
                  find_path(from->right, to, path)))
            {
                path.pop_back();
                return false;
            }

            return true;
        }

        return false;
    }

    std::string getDirections(TreeNode* root, int start_value, int dest_value)
    {
        std::vector<TreeNode*> paths;
        paths.reserve(64);

        // lazy way to do separate lookup for each node but good enough to pass
        find_path(root, start_value, paths);
        size_t to_start_len = paths.size();
        find_path(root, dest_value, paths);
        auto to_start = std::span{paths}.subspan(0, to_start_len);
        auto to_dest = std::span{paths}.subspan(to_start_len);

        // Cut the path to LCA
        {
            size_t i = 0;
            size_t i_end = std::min(to_start.size(), to_dest.size());
            while (i != i_end && to_start[i] == to_dest[i]) ++i;
            to_start = to_start.subspan(i);
            to_dest = to_dest.subspan(i - 1);  // leave LCA in to_dest
        }

        // encode path into a string
        std::string result;

        // encode start
        for (size_t i = 0; i != to_start.size(); ++i)
        {
            result.push_back('U');
        }

        // encode lca -> dest
        if (size_t n = to_dest.size(); n > 1)
        {
            for (size_t i = 0; i != n - 1; ++i)
            {
                result.push_back(
                    to_dest[i + 1] == to_dest[i]->left ? 'L' : 'R');
            }
        }

        return result;
    }
};
