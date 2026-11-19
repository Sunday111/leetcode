#pragma once

#include <unordered_map>
#include <vector>

class Node
{
public:
    int val;
    std::vector<Node*> neighbors{};
};

class Solution
{
public:
    Node* cloneGraph(Node* old_root)
    {
        if (!old_root) return nullptr;

        std::unordered_map<Node*, Node*> old_to_new;
        auto new_root = new Node(old_root->val);  // NOLINT
        old_to_new[old_root] = new_root;

        std::vector<Node*> queue{old_root};

        while (!queue.empty())
        {
            auto old_node = queue.back();
            queue.pop_back();

            auto new_node = old_to_new[old_node];
            new_node->neighbors.reserve(old_node->neighbors.size());

            for (Node* old_child : old_node->neighbors)
            {
                Node* new_child = [&]
                {
                    if (auto it = old_to_new.find(old_child);
                        it != old_to_new.end())
                    {
                        return it->second;
                    }

                    auto new_child = new Node(old_child->val);  // NOLINT
                    old_to_new[old_child] = new_child;
                    queue.push_back(old_child);
                    return new_child;
                }();

                new_node->neighbors.push_back(new_child);
            }
        }

        return new_root;
    }
};
