#include <concepts>
#include <vector>

using u32 = uint32_t;

#define FORCE_INLINE inline __attribute__((always_inline))
#define INLINE_LAMBDA __attribute__((always_inline))

// Swaps a and b if a > b. Only for integers. Branchless
template <std::integral Int>
FORCE_INLINE static constexpr void swap_if_greater(Int& a, Int& b) noexcept
{
    Int mask = (a ^ b) & -Int{a > b};
    a ^= mask, b ^= mask;
}

class Solution
{
public:
    [[nodiscard]] static constexpr auto maxProductDifference(
        const std::vector<u32>& nums) noexcept
    {
        u32 lowest = 0xFFFFFFFF, low = lowest;
        u32 highest = 0, high = 0;

        for (u32 x : nums)
        {
            auto t1 = x, t2 = x;
            swap_if_greater(t1, high);
            swap_if_greater(high, highest);
            swap_if_greater(low, t2);
            swap_if_greater(lowest, low);
        }

        return highest * high - low * lowest;
    }

    [[nodiscard]] static auto maxProductDifference(
        const std::vector<int>& nums) noexcept
    {
        return maxProductDifference(
            reinterpret_cast<const std::vector<u32>&>(nums));
    }
};
