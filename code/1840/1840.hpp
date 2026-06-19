#include <algorithm>
#include <ranges>
#include <vector>

#include "integral_aliases.hpp"

class Solution
{
public:
    u32 maxBuilding(
        const u32 n,
        std::vector<std::vector<int>>& restrictions) noexcept
    {
        std::ranges::sort(restrictions);
        auto& rstr =
            reinterpret_cast<std::vector<std::vector<u32>>&>(restrictions);
        u32 i = 1, i_max = 0;
        for (auto& x : rstr)
        {
            auto &k = x[0], &k_max = x[1];
            u32 l = k - i;
            k_max = std::min(k_max, i_max + l);
            i = k, i_max = k_max;
        }
        u32 j = n, j_max = i_max + n - i, r = 0;
        for (auto& prev : rstr | std::views::reverse)
        {
            i = prev[0], i_max = prev[1];
            i_max = std::min(i_max, j_max + j - i);
            u32 lo = std::min(i_max, j_max), hi = std::max(i_max, j_max);
            r = std::max(r, hi + (j - i - hi + lo) / 2);
            j = i, j_max = i_max;
        }
        r = std::max(r, j_max + (j - j_max - 1) / 2);
        return r;
    }
};
