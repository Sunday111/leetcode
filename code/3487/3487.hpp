#pragma once

#include <bitset>
#include <vector>

class Solution
{
public:
    int maxSum(std::vector<int>& nums)
    {
        std::bitset<101> s{};
        int m = -100, r = 0;
        for (int v : nums)
        {
            uint8_t k = v > 0 ? v & 0xFF : 0;
            r += (!s[k]) * k;
            s[k] = true;
            m = v > m ? v : m;
        }
        return r ? r : m;
    }
};
