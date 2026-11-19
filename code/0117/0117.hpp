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
    Node* connect(Node* root)
    {
        std::queue<Node*> q;
        if (root) q.push(root);

        auto enqueue = [&](Node* n)
        {
            if (n) q.push(n);
        };

        while (!q.empty())
        {
            auto* prev = q.front();
            q.pop();
            size_t k = q.size();

            enqueue(prev->left);
            enqueue(prev->right);
            for (size_t i = 0; i != k; ++i)
            {
                auto* node = q.front();
                q.pop();
                enqueue(node->left);
                enqueue(node->right);

                prev->next = node;
                prev = node;
            }
        }

        return root;
    }
};
