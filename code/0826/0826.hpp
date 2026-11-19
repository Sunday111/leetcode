#pragma once

#include <algorithm>
#include <vector>

class Solution
{
public:
    using u32 = uint32_t;
    [[nodiscard]] static int maxProfitAssignment(
        const std::vector<int>& difficulty,
        std::vector<int>& profit,
        std::vector<int>& worker) noexcept
    {
        // difficulty to profit
        static std::array<int, 100'001> dtp;

        int max_difficulty = 0;
        for (u32 i = 0; i != profit.size(); ++i)
        {
            int d = difficulty[i];
            auto& p = dtp[static_cast<u32>(d)];
            p = std::max(p, profit[i]);
            max_difficulty = std::max(max_difficulty, d);
        }

        const int max_ability = *std::ranges::max_element(worker);
        std::partial_sum(
            dtp.begin(),
            std::next(dtp.begin(), max_ability + 1),
            dtp.begin(),
            [](auto a, auto b) { return std::max(a, b); });

        int r = 0;
        for (int ability : worker) r += dtp[static_cast<u32>(ability)];

        // cleanup used area
        std::fill_n(dtp.begin(), std::max(max_ability, max_difficulty) + 1, 0);

        return r;
    }
};
