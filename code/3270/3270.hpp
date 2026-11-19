#pragma once

#include <algorithm>
class Solution
{
public:
    [[nodiscard]] static constexpr int
    generateKey(int num1, int num2, int num3) noexcept
    {
        int r = 0;
        for (int m = 1; m != 10000; m *= 10)
        {
            r += m * std::min({num1 % 10, num2 % 10, num3 % 10});
            num1 /= 10, num2 /= 10, num3 /= 10;
        }
        return r;
    }
};
