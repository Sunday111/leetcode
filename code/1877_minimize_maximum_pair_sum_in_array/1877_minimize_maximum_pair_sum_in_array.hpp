#include <algorithm>
#include <vector>

#include "radix_sorter.hpp"

class Solution
{
public:
    [[nodiscard]] static constexpr u32 minPairSum(
        std::vector<u32>& nums) noexcept
    {
        radix_sort<6, 3>(std::span{nums});
        u32 n = static_cast<u32>(nums.size()), ans = 0;
        for (uint32_t l = 0, r = n - 1; l < r; ++l, --r)
        {
            ans = std::max(ans, nums[l] + nums[r]);
        }
        return ans;
    }

    [[nodiscard]] static constexpr u32 minPairSum(
        std::vector<int>& nums) noexcept
    {
        return minPairSum(reinterpret_cast<std::vector<u32>&>(nums));
    }
};
