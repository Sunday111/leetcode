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
        ListNode stub{{}, head};
        ListNode *prev = &stub, *a = head;
        while (a && a->next)
        {
            auto b = a->next;
            auto c = b->next;
            a->next = c;
            b->next = a;
            prev->next = b;
            prev = a;
            a = c;
        }

        return stub.next;
    }
};
