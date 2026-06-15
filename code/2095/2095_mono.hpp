#include <utility>




#ifdef LC_LOCAL_BUILD

struct ListNode
{
    int val{};
    ListNode* next{};
};

#endif

inline static constexpr auto ll_find_mid_and_prev =
    [] [[nodiscard, gnu::always_inline]]
    (ListNode * x) noexcept -> std::pair<ListNode*, ListNode*>
{
    ListNode* p = nullptr;
    for (auto y = x; y && y->next;)
    {
        p = std::exchange(x, x->next);
        y = y->next->next;
    }

    return {p, x};
};

class Solution
{
public:
    ListNode* deleteMiddle(ListNode* head)
    {
        auto [p, m] = ll_find_mid_and_prev(head);
        if (p && m) p->next = m->next;
        return head;
    }
};
