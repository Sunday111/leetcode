#pragma once

#include <array>
class Solution
{
public:
    static constexpr std::array kFactors{2, 3, 5};

    bool isUgly(int n)
    {
        if (n == 0) return false;
        for (int k : kFactors)
        {
            while (n % k == 0)
            {
                n /= k;
            }
        }
        return n == 1;
    }
};
