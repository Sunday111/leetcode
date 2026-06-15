#pragma once

#include <utility>

#include "singly_linked_list/ll_node.hpp"

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
