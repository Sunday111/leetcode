#pragma once

#include <cstdint>

class Solution
{
public:
    using u16 = uint16_t;
    [[nodiscard]] static constexpr u16 findTheWinner(u16 n, u16 k) noexcept
    {
        u16 ans = 0;
        for (u16 i = 2; i <= n; i++) ans = (ans + k) % i;
        return ans + 1;
    }
};
