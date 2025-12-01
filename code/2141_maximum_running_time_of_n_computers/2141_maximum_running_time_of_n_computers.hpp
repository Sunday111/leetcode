#pragma once

#include <ranges>
#include <vector>

#include "bisect.hpp"
#include "integral_aliases.hpp"
#include "radix_sorter.hpp"
#include "sum.hpp"

class Solution
{
public:
    u64 maxRunTime(u32 n, std::vector<int>& batteries_)
    {
        auto batteries = reinterpret_range<u32>(batteries_);
        radix_sort<10, 3, SortOrder::Descending>(batteries);

        const std::span<const u32> active = batteries.first(n);
        const std::span<const u32> swaps = batteries.last(batteries.size() - n);
        if (swaps.empty()) return active.back();

        const u64 total = sum(batteries, u64{0});
        if (n == 1) return total;

        auto test = [&](u64 target) -> bool
        {
            if (active.back() >= target) return true;

            u32 rem = 0, next = 0;

            for (u32 charge : active | std::views::reverse)
            {
                if (charge >= target) break;

                u64 need = target - charge;
                while (need > rem && next != swaps.size())
                {
                    need -= rem;
                    rem = swaps[next++];
                }

                if (need > rem) return false;
                rem -= need;
            }

            return true;
        };

        return *bisectLastTrue(
            std::views::iota(u64{batteries.back()}, (total / u64{n}) + 1),
            test);
    }
};
