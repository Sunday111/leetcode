#pragma once

#include <array>
#include <vector>

class Solution
{
public:
    void wiggleSort(std::vector<int>& nums)
    {
        std::array<uint16_t, 5001> c{};
        for (const int& v : nums) c[std::bit_cast<unsigned>(v)]++;

        uint16_t j = c.size() - 1;
        auto get_biggest = [&]
        {
            while (c[j] == 0) --j;
            --c[j];
            return j;
        };

        for (uint16_t i = 1; i < nums.size(); i += 2) nums[i] = get_biggest();
        for (uint16_t i = 0; i < nums.size(); i += 2) nums[i] = get_biggest();
    }
};
