#include <vector>

#include "integral_aliases.hpp"

class Solution
{
public:
    [[nodiscard]] static constexpr u32 minimumPrefixLength(
        const std::vector<int>& nums) noexcept
    {
        u32 i = static_cast<u32>(nums.size() - 1);
        while (i-- && nums[i] < nums[i + 1]);
        return i - 0xFFFFFFFF;
    }
};
