#pragma once

#include <alloca.h>

#include <algorithm>
struct ListNode
{
    int val = 0;
    ListNode* next = nullptr;
};

class Solution
{
public:
    ListNode* sortList(ListNode* head)
    {
        if (head)
        {
            int* const values =
                reinterpret_cast<int*>(alloca(sizeof(int) * 50'000));  // NOLINT

            int* p = values;
            for (auto h = head; h != nullptr; h = h->next)
            {
                *p++ = h->val;  // NOLINT
            }

            std::sort(values, p);

            p = values;
            for (auto h = head; h != nullptr; h = h->next)
            {
                h->val = *p++;  // NOLINT
            }
        }
        return head;
    }
};
