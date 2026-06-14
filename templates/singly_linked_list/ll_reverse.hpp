#include <utility>

#include "ll_node.hpp"

inline static constexpr auto ll_reverse =
    [] [[nodiscard, gnu::always_inline]] (ListNode * head) noexcept -> ListNode*
{
    ListNode *tmp = head, *next = nullptr, *prev = nullptr;

    while (tmp)
    {
        next = std::exchange(tmp->next, prev);
        prev = std::exchange(tmp, next);
    }

    return prev;
};
