#pragma once

#include <vector>

class Solution
{
public:
    [[nodiscard]] static constexpr bool carPooling(
        const std::vector<std::vector<int>>& trips,
        int32_t capacity)
    {
        std::array<int32_t, 1001> diff{};

        uint16_t max_src = 0;
        uint16_t min_src = 1001;
        for (auto& trip : trips)
        {
            int num = trip[0];
            uint16_t src = trip[1] & 0xFFFF, dst = trip[2] & 0xFFFF;
            min_src = std::min(min_src, src);
            max_src = std::max(max_src, dst);
            diff[src] += num;
            diff[dst] -= num;
        }

        int sum = 0;
        ++max_src;
        for (uint16_t i = min_src; i != max_src; ++i)
        {
            sum += diff[i];
            if (sum > capacity)
            {
                return false;
            }
        }

        return true;
    }
};
