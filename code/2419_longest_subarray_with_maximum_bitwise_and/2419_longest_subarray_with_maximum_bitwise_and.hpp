#pragma once

#include <vector>

class Solution
{
public:
    [[nodiscard]] static constexpr int longestSubarray(
        std::vector<int>& nums) noexcept
    {
        int m = 0, mc = 0, c = 0;
        for (int v : nums)
        {
            c += (v == m) - (v != m) * (c - (v > m));
            mc = std::max(mc * !(v > m), c);
            m = std::max(m, v);
        }

        return mc;
    }
};
