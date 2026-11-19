#pragma once

#include <tuple>

struct ListNode
{
    int val;
    ListNode* next;
};

class Solution
{
public:
    // returns new head of the group and next element after the group
    [[nodiscard]] static constexpr std::tuple<ListNode*, ListNode*>
    reverseGroup(ListNode* head, int k) noexcept
    {
        auto prev = head->next;
        auto curr = prev->next;
        prev->next = head;
        --k;

        while (--k)
        {
            auto cn = curr->next;
            curr->next = prev;
            prev = curr;
            curr = cn;
        }

        return {prev, curr};
    }

    [[nodiscard]] static constexpr ListNode* reverseKGroup(
        ListNode* head,
        const int k) noexcept
    {
        if (k == 1) return head;

        // Compute the list head
        int l = 0;
        for (auto p = head; p; p = p->next) ++l;

        int groups = l / k;

        if (groups == 0) return head;

        // Do the first iteration separately to record the new list head
        auto tail = head;
        std::tie(head, tail->next) = reverseGroup(head, k);

        while (--groups)
        {
            auto next_tail = tail->next;
            std::tie(tail->next, next_tail->next) = reverseGroup(next_tail, k);
            tail = next_tail;
        }

        return head;
    }
};
