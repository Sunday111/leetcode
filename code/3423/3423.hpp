#pragma once

#include <vector>

class Solution
{
public:
    using u8 = uint8_t;
    [[nodiscard]] static constexpr u8 maxAdjacentDistance(
        const std::vector<int>& nums) noexcept
    {
        u8 r = 0, li = static_cast<u8>(nums.size() - 1);
        // Compare neighbor elements
        for (u8 i = 0; i != li; ++i)
        {
            u8 d = std::abs(nums[i] - nums[i + 1]) & 0xFF;
            r = std::max(r, d);
        }

        // as this buffer is circular compare
        // the first and the last ones
        u8 d = std::abs(nums[0] - nums[li]) & 0xFF;
        return std::max(r, d);
    }
};
