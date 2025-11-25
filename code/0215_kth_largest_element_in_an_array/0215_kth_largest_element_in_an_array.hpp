#include <array>
#include <vector>

using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

#define FORCE_INLINE inline __attribute__((always_inline))

class Solution
{
public:
    static constexpr u16 kValueLimit = 20'002;
    static constexpr u16 kLayer0 = (kValueLimit >> 6) + 1;
    static constexpr u16 kLayer1 = (kLayer0 >> 6) + 1;
    std::array<u32, kValueLimit> freq{};
    std::array<u64, kLayer0> bs0{};
    std::array<u64, kLayer1> bs1{};
    u64 bs2{};
    static_assert(kLayer1 <= 64);

    FORCE_INLINE constexpr void add(u16 v) noexcept
    {
        ++freq[v];
        u16 wi0 = v >> 6, wi1 = wi0 >> 6;
        bs0[wi0] |= u64{1} << (v & 63);
        bs1[wi1] |= u64{1} << (wi0 & 63);
        bs2 |= u64{1} << (wi1 & 63);
    }

    FORCE_INLINE constexpr void rem(u16 v) noexcept
    {
        u16 wi0 = v >> 6, bi0 = v & 63;
        u16 wi1 = wi0 >> 6, bi1 = wi0 & 63;
        u16 bi2 = wi1 & 63;
        bs0[wi0] &= ~(u64{!--freq[v]} << bi0);
        bs1[wi1] &= ~(u64{!bs0[wi0]} << bi1);
        bs2 &= ~(u64{!bs1[wi1]} << bi2);
    }

    [[nodiscard]] FORCE_INLINE constexpr u16 min_element() const noexcept
    {
        auto wi1 = std::countr_zero(bs2);
        auto bi1 = std::countr_zero(bs1[wi1 & 0xFFFF]);
        auto wi0 = (wi1 << 6) | bi1, bi0 = std::countr_zero(bs0[wi0 & 0xFFFF]);
        return ((wi0 << 6) | bi0) & 0xFFFF;
    }

    [[nodiscard]] constexpr int findKthLargest(
        const std::vector<int>& nums,
        const u32 k) noexcept
    {
        for (u32 i = 0; i != k; ++i)
        {
            add(static_cast<u16>(nums[i] + 10'000));
        }

        const u32 n = static_cast<u32>(nums.size());
        for (u32 i = k; i != n; ++i)
        {
            add(static_cast<u16>(nums[i] + 10'000));
            rem(min_element());
        }

        return static_cast<int>(min_element()) - 10'000;
    }
};
