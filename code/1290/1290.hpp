#pragma once

struct ListNode
{
    int val;
    ListNode* next;
};

class Solution
{
public:
    [[nodiscard]] static constexpr int getDecimalValue(ListNode* h) noexcept
    {
        int r = 0;
        for (; h; h = h->next) r = (r << 1) | h->val;
        return r;
    }
};
