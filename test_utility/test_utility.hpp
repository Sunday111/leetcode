#pragma once

#include <queue>

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
template <typename Node>
bool CompareBinaryTrees(Node* root_a, Node* root_b)
{
    std::queue<std::pair<Node*, Node*>> q{{root_a, root_b}};

    while (!q.empty())
    {
        auto [a, b] = q.front();
        q.pop();

        if (static_cast<bool>(a) ^ static_cast<bool>(b)) return false;
        if (!a) continue;
        if (a->val != b->val) return false;

        q.emplace(a->left, b->left);
        q.emplace(a->right, b->right);
    }

    return true;
}
