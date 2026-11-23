#include <cstdint>
#include <vector>

#include "bitsets/bitset_view/bsv_get.hpp"
#include "bitsets/bitset_view/bsv_set.hpp"
#include "ptr_if.hpp"
#include "singly_linked_list/ll_node.hpp"

class Solution
{
public:
    using u64 = uint64_t;
    inline static u64 b[(100'001 / 64) + 1];
    static constexpr BitsetView<u64, 100'001> bits{b};
    inline static int dirty = 0;

    [[nodiscard, gnu::always_inline]] inline static bool is_set(int v) noexcept
    {
        return bsv_get(bits, static_cast<std::size_t>(v));
    }

    [[nodiscard]] static ListNode* modifiedList(
        const std::vector<int>& nums,
        ListNode* head) noexcept
    {
        std::fill_n(b, dirty + 1, u64{});
        dirty = 0;

        for (int v : nums)
        {
            bsv_set<true>(bits, static_cast<std::size_t>(v));
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
