#pragma once

#include <algorithm>
#include <array>
#include <vector>

class Solution
{
public:
    void sortColors(std::vector<int>& nums)
    {
        std::array<uint16_t, 3> count{};
        for (const auto& v : nums)
        {
            count[static_cast<uint8_t>(v)]++;
        }
        auto it = nums.begin();
        for (int v = 0; v != 3; ++v)
        {
            it = std::fill_n(it, count[std::bit_cast<unsigned>(v)], v);
        }
    }
};
