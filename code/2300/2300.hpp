#pragma once

#include <algorithm>
#include <vector>

class Solution
{
public:
    using u32 = uint32_t;
    using i64 = int64_t;
    [[nodiscard]] static constexpr std::vector<int> successfulPairs(
        std::vector<int>& spells,
        std::vector<int>& potions,
        i64 success) noexcept
    {
        std::ranges::sort(spells);

        for (int& spell : spells)
        {
            auto target = success / spell;
            auto it = success % spell
                          ? std::ranges::upper_bound(potions, target)
                          : std::ranges::lower_bound(potions, target);
            spell = static_cast<int>(std::distance(it, potions.end()));
        }

        return std::move(spells);
    }
};
