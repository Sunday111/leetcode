#pragma once

#include <algorithm>
#include <queue>
#include <vector>

struct ListNode
{
    int val = 0;
    ListNode* next = nullptr;
};

class Solution
{
public:
    ListNode* mergeKLists(std::vector<ListNode*>& lists)
    {
        constexpr auto cmp_ = [](const ListNode* a, const ListNode* b)
        {
            return a->val > b->val;
        };

        std::priority_queue<ListNode*, std::vector<ListNode*>, decltype(cmp_)>
            q;

        auto pop = [&]
        {
            auto v = q.top();
            q.pop();
            return v;
        };

        auto push = [&](ListNode* node)
        {
            if (node) q.push(node);
        };

        std::ranges::for_each(lists, push);

        if (q.empty()) return nullptr;

        auto head = pop();
        push(head->next);
        auto prev = head;
        while (!q.empty())
        {
            auto node = pop();
            push(node->next);
            prev->next = node;
            prev = node;
        }

        return head;
    }
};
