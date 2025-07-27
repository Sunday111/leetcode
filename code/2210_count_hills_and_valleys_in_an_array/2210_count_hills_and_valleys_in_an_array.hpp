#pragma once

#include <vector>

class Solution
{
public:
    using u8 = uint8_t;
    [[nodiscard]] static constexpr u8 countHillValley(
        std::vector<int>& nums) noexcept
    {
        u8 n = 0, p = 0;
        for (int v : nums)
        {
            nums[n] = v;
            n += p != v;
            p = v & 0xFF;
        }

        --n;
        u8 r = 0;
        for (u8 i = 1; i < n; ++i)
        {
            r += ((nums[i - 1] < nums[i]) == (nums[i + 1] < nums[i]));
        }

        return r;
    }
};
