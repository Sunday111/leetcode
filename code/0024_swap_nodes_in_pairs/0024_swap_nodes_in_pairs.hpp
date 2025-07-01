#pragma once

struct ListNode
{
    int val;
    ListNode* next;
};

class Solution
{
public:
    [[nodiscard]] static constexpr ListNode* swapPairs(ListNode* head) noexcept
    {
        ListNode* const r = head && head->next ? head->next : head;

        ListNode stub{.next = head};

        ListNode* prev = nullptr;
        ListNode* a = head;

        while (a && a->next)
        {
            auto b = a->next;
            auto c = b->next;
            if (prev) prev->next = b;
            a->next = c;
            b->next = a;
            prev = a;
            a = c;
        }

        return r;
    }
};
