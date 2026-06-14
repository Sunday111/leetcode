
#include <algorithm>

#include "singly_linked_list/ll_find_mid.hpp"
#include "singly_linked_list/ll_reverse.hpp"

class Solution
{
public:
    int pairSum(ListNode* head) const noexcept
    {
        int r = 0;
        auto mid = ll_reverse(ll_find_mid(head));
        while (mid)
        {
            r = std::max(head->val + mid->val, r);
            head = head->next;
            mid = mid->next;
        }
        return r;
    }
};

#include "sync_stdio.hpp"
