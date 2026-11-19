#pragma once

#include <algorithm>
#include <vector>

class Solution
{
public:
    using u32 = uint32_t;
    [[nodiscard]] static constexpr int maximumEnergy(
        std::vector<int>& energy,
        u32 k)
    {
        u32 n = static_cast<u32>(energy.size());
        for (u32 t = n; t-- > k;)
        {
            energy[t - k] += energy[t];
        }
        return *std::ranges::max_element(energy);
    }
};
