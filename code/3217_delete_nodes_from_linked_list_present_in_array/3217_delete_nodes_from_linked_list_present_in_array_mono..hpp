#include <bit>
#include <concepts>
#include <type_traits>
#include <vector>

#define FORCE_INLINE inline __attribute__((always_inline))

#define HOT_PATH __attribute__((hot))

template <std::integral T>
[[nodiscard]] FORCE_INLINE HOT_PATH constexpr T iif(bool c, T a, T b) noexcept
{
    return (a & static_cast<T>(-c)) + (b & static_cast<T>(~static_cast<T>(-c)));
}

template <typename T>
    requires(std::is_pointer_v<T>)
[[nodiscard]] FORCE_INLINE HOT_PATH constexpr T iif(bool c, T a, T b) noexcept
{
    return std::bit_cast<T>(
        iif(c, std::bit_cast<std::size_t>(a), std::bit_cast<std::size_t>(b)));
}

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
            last = iif(is_set(p->val), last, p);
        }
        last->next = nullptr;

        return head;
    }
};
