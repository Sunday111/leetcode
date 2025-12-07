#include <algorithm>
#include <vector>

#include "reverse_bits_32.hpp"

class Solution
{
public:
    FORCE_INLINE static constexpr u32 reverse(u32 x) noexcept
    {
        return reverse32(x) >> std::countl_zero(x);
    }

    FORCE_INLINE static constexpr std::pair<u32, int> proj(int x) noexcept
    {
        return {reverse(std::bit_cast<u32>(x)), x};
    }

    static constexpr std::vector<int> sortByReflection(
        std::vector<int>& nums) noexcept
    {
        std::ranges::sort(nums, std::less{}, proj);
        return std::move(nums);
    }
};
