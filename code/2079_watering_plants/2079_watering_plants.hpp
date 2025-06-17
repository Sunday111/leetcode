#pragma once

#include <vector>

class Solution
{
public:
    using u32 = uint32_t;
    [[nodiscard]] static constexpr u32 wateringPlants(
        const std::vector<int>& plants,
        int capacity) noexcept
    {
        const u32 n = static_cast<u32>(plants.size());
        u32 steps = 0;
        int can = capacity;

        for (u32 i = 0; i != n; ++i)
        {
            const int required = plants[i];
            if (can < required)
            {
                steps += i;
                can = capacity;
            }

            can -= required;
        }

        return steps * 2 + n;
    }
};
