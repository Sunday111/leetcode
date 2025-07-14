#pragma once

#include <utility>

class Solution
{
public:
    [[nodiscard]] static constexpr bool isHappy(int n) noexcept
    {
        while (n != 1 && n != 4)
        {
            for (int k = std::exchange(n, 0); k; k /= 10)
            {
                n += (k % 10) * (k % 10);
            }
        }

        return n == 1;
    }
};
