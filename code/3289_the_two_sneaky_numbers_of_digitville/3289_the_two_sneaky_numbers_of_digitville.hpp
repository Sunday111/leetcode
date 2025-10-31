#pragma once

#include <bitset>
#include <vector>

class Solution
{
public:
    std::vector<int> getSneakyNumbers(std::vector<int>& nums)
    {
        std::bitset<101> b;
        size_t k = 0;
        size_t n = nums.size();
        for (size_t i = 0; i != n && k != 2; ++i)
        {
            uint8_t v = nums[i] & 0xFF;
            nums[k] = v;
            k += b[v];
            b[v] = 1;
        }

        nums.resize(2);
        return std::move(nums);
    }
};
