#pragma once

#include <queue>

// Definition for a Node.
class Node
{
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node( // NOLINT
        int _val = 0,
        Node* _left = nullptr,
        Node* _right = nullptr,
        Node* _next = nullptr)
        : val(_val),
          left(_left),
          right(_right),
          next(_next)
    {
    }
};

class Solution
{
public:
    inline static constexpr size_t kMaxNodes = 4096;

    Node* connect(Node* root)
    {
        std::queue<Node*> q;
        if (root) q.push(root);

        while (!q.empty())
        {
            auto* prev = q.front();
            q.pop();
            size_t k = q.size();

            if (prev->left)
            {
                q.push(prev->left);
                q.push(prev->right);
                for (size_t i = 0; i != k; ++i)
                {
                    auto* node = q.front();
                    q.pop();
                    q.push(node->left);
                    q.push(node->right);

                    prev->next = node;
                    prev = node;
                }
            }
            else
            {
                for (size_t i = 0; i != k; ++i)
                {
                    auto* n = q.front();
                    q.pop();
                    prev->next = n;
                    prev = n;
                }
            }
        }

        return root;
    }
};
