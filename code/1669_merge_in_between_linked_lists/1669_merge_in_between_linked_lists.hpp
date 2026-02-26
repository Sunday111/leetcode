#include "exch.hpp"
#include "lc_signly_linked_list_node.hpp"

class Solution
{
public:
    [[nodiscard]] static constexpr ListNode*
    mergeInBetween(ListNode* l1, int a, int b, ListNode* l2) noexcept
    {
        b -= a - 1;
        auto r = l1;
        while (--a) l1 = l1->next;
        l1 = exch(l1->next, l2);
        while (b--) l1 = l1->next;
        while (l2->next) l2 = l2->next;
        l2->next = l1;
        return r;
    }
};
