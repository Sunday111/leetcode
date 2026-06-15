#pragma once

#include "singly_linked_list/ll_node.hpp"

inline static constexpr auto ll_find_mid = [] [[nodiscard, gnu::always_inline]]
                                           (ListNode * x) noexcept -> ListNode*
{
    for (auto y = x; y && y->next;)
    {
        x = x->next;
        y = y->next->next;
    }

    return x;
};
