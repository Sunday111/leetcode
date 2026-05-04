#include <utility>

#include "lc_signly_linked_list_node.hpp"

class Solution
{
public:
    ListNode* rotateRight(ListNode* h, int k)
    {
        if (!k || !h || !h->next) return h;
        auto t = h;
        int n = 0;
        for (auto m = h; m; ++n) t = std::exchange(m, m->next);

        auto x = h;
        if (auto x1 = x; (k = (n - (k % n)) % n))
        {
            while (k--) x1 = std::exchange(x, x->next);
            t->next = h;
            x1->next = nullptr;
        }
        return x;
    }
};
