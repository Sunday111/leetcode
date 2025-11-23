#include <vector>

#include "force_inline.hpp"
#include "ptr_if.hpp"

struct ListNode
{
    int val{};
    ListNode* next{};
};

class Solution
{
public:
    using u64 = uint64_t;
    inline static u64 b[(100'001 / 64) + 1];
    inline static int dirty = 0;

    [[nodiscard]] FORCE_INLINE static bool is_set(int v) noexcept
    {
        return b[v >> 6] & (u64{1} << (v & 63));
    }

    [[nodiscard]] static ListNode* modifiedList(
        const std::vector<int>& nums,
        ListNode* head) noexcept
    {
        std::fill_n(b, dirty + 1, u64{});
        dirty = 0;

        for (int v : nums)
        {
            b[v >> 6] |= u64{1} << (v & 63);
            dirty = std::max(dirty, v >> 6);
        }

        while (is_set(head->val)) head = head->next;

        auto last = head;
        for (auto p = head->next; p; p = p->next)
        {
            last->next = p;
            last = ptrif(is_set(p->val), last, p);
        }
        last->next = nullptr;

        return head;
    }
};
