#pragma once

#include <numeric>
#include <vector>

class Solution
{
public:
    using u32 = uint32_t;
    using i64 = int64_t;
    [[nodiscard]] static constexpr i64 minTime(
        std::vector<int>& wizards,
        const std::vector<int>& potions)
    {
        std::partial_sum(wizards.begin(), wizards.end(), wizards.begin());
        i64 start = 0;

        for (u32 potion = 1; potion != potions.size(); ++potion)
        {
            const i64 current_potion = potions[potion];
            const i64 previous_potion = potions[potion - 1];
            i64 t = i64{wizards[0]} * previous_potion;
            for (u32 wizard = 1; wizard != wizards.size(); ++wizard)
            {
                i64 alt = wizards[wizard] * previous_potion -
                          wizards[wizard - 1] * current_potion;
                t = std::max(t, alt);
            }
            start += t;
        }
        return start + i64{wizards.back()} * i64{potions.back()};
    }
};
