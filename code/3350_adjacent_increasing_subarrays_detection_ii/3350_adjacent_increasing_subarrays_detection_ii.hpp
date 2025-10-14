#pragma once

#include <vector>

using u32 = uint32_t;

class Solution
{
public:
    static u32 maxIncreasingSubarrays(const std::vector<int>& nums) noexcept
    {
        u32 l = 0, prev = 0, mp = 0, ml = 0;
        int pv = std::numeric_limits<int>::lowest();
        for (int v : nums)
        {
            if (v <= std::exchange(pv, v))
            {
                mp = std::max(mp, std::min(prev, l));
                ml = std::max(ml, l);
                prev = std::exchange(l, 0);
            }
            ++l;
        }
        mp = std::max(mp, std::min(prev, l));
        ml = std::max(ml, l);
        return std::max(ml / 2, mp);
    }
};
