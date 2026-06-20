#include <algorithm>
#include <ranges>
#include <vector>

#include "integral_aliases.hpp"
#include "radix_sorter.hpp"

class Solution
{
public:
    inline static std::pair<u32, u32> rstr[100'000]{};

    u32 maxBuilding(
        const u32 n,
        std::vector<std::vector<int>>& restrictions) noexcept
    {
        u32 nr = 0;
        for (auto t :
             reinterpret_cast<std::vector<std::vector<u32>>&>(restrictions))
        {
            rstr[nr++] = {t[0], t[1]};
        }

        radix_sort<10, 3>(std::span{reinterpret_cast<u64*>(rstr), nr});

        u32 i = 1, i_max = 0;
        for (auto& [k, k_max] : rstr | std::views::take(nr))
        {
            k_max = std::min(k_max, i_max + k - i);
            i = k, i_max = k_max;
        }

        u32 j = n, j_max = i_max + n - i, r = 0;
        for (auto& prev : rstr | std::views::take(nr) | std::views::reverse)
        {
            std::tie(i, i_max) = prev;
            i_max = std::min(i_max, j_max + j - i);
            u32 lo = std::min(i_max, j_max), hi = std::max(i_max, j_max);
            r = std::max(r, hi + (j - i - hi + lo) / 2);
            j = i, j_max = i_max;
        }
        r = std::max(r, j_max + (j - j_max - 1) / 2);
        return r;
    }
};
