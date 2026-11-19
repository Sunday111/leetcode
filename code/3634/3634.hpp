#include <vector>

#include "radix_sorter.hpp"

class Solution
{
public:
    [[nodiscard]] static constexpr u32 minRemoval(
        std::vector<u32>& nums,
        u32 k) noexcept
    {
        radix_sort<10, 3>(std::span{nums});
        u32 n = static_cast<u32>(nums.size()), x = 1;
        u64 lim = 0;
        for (u32 i = ~u32{}, j = 0; j != n; ++j)
        {
            if (nums[j] > lim)
            {
                ++i;
                lim = u64{nums[i]} * k;
            }
            else
            {
                ++x;
            }
        }

        return n - x;
    }

    [[nodiscard]] static u32 minRemoval(std::vector<int>& nums, u32 k) noexcept
    {
        return minRemoval(reinterpret_cast<std::vector<u32>&>(nums), k);
    }
};
