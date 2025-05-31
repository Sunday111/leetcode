#pragma once

#include <array>

class Solution
{
public:
    [[nodiscard]] static constexpr int clumsy(int n)
    {
        int r = n--;
        if (n) r *= n--;
        if (n) r /= n--;
        if (n) r += n--;
        if (int k = n / 4; k)
        {
            if ((n % 4) == 0) --k;
            n -= 4 * k;
            r -= 4 * k;
        }

        constexpr std::array tail{0, 1, 2, 6, 5};
        return r - tail[std::bit_cast<uint32_t>(n)];
    }
};
