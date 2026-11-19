#pragma once

struct ListNode
{
    int val = 0;
    ListNode* next = nullptr;
};

class Solution
{
public:
    int removeNthFromEndR(ListNode* head, int n)
    {
        if (!head) return 0;

        auto k = removeNthFromEndR(head->next, n);

        if (k == n)
        {
            head->next = head->next->next;
        }

        return k + 1;
    }

    ListNode* removeNthFromEnd(ListNode* head, int n)
    {
        if (removeNthFromEndR(head, n) == n)
        {
            return head->next;
        }

        return head;
    }
};
