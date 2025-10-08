#pragma once

#include <algorithm>
#include <vector>

class Solution
{
public:
    using i64 = int64_t;
    [[nodiscard]] static constexpr std::vector<int> successfulPairs(
        std::vector<int>& spells,
        const std::vector<int>& potions,
        i64 success) noexcept
    {
        using u32 = uint32_t;
        u32 k = static_cast<u32>(*std::ranges::max_element(spells) + 1);
        static std::array<int, 100'003> freq;
        std::ranges::fill_n(freq.begin(), k, 0);

        for (int potion : potions)
        {
            ++freq[std::min(
                static_cast<u32>((success + potion - 1) / potion),
                k)];
        }

        std::partial_sum(
            freq.begin(),
            std::next(freq.begin(), k),
            freq.begin());

        for (u32 i = 0; i != spells.size(); ++i)
        {
            spells[i] = freq[static_cast<u32>(spells[i])];
        }

        return std::move(spells);
    }
};
