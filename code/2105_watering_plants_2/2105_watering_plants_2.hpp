#pragma once

#include <vector>

class Solution
{
public:
    using u32 = uint32_t;
    [[nodiscard]] static constexpr u32 minimumRefill(
        const std::vector<int>& plants,
        int capacityA,
        int capacityB) noexcept
    {
        const u32 n = static_cast<u32>(plants.size());
        int canA = capacityA, canB = capacityB;
        u32 refills = 0;
        u32 a = 0, b = n - 1;

        while (a < b)
        {
            const int reqA = plants[a++], reqB = plants[b--];
            if (canA < reqA)
            {
                canA = capacityA;
                ++refills;
            }
            canA -= reqA;

            if (canB < reqB)
            {
                canB = capacityB;
                ++refills;
            }
            canB -= reqB;
        }

        if (a == b && std::max(canA, canB) < plants[a])
        {
            ++refills;
        }

        return refills;
    }
};
