#include "singly_linked_list/ll_find_mid_and_prev.hpp"

class Solution
{
public:
    ListNode* deleteMiddle(ListNode* head) noexcept
    {
        auto [p, m] = ll_find_mid_and_prev(head);
        if (p && m) p->next = m->next;
        return head;
    }
};
