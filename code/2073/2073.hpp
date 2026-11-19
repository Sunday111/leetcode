#pragma once

#include <vector>

class Solution
{
public:
    using u16 = uint16_t;
    using u8 = uint8_t;
    [[nodiscard]] constexpr u16 timeRequiredToBuy(
        std::vector<int>& tickets,
        u8 k) noexcept
    {
        const u8 nk = tickets[k] & 0xFF;
        const u8 n = tickets.size() & 0xFF;
        u16 r = nk;

        for (u8 i = 0; i != k; ++i)
        {
            r += std::min<u8>(tickets[i] & 0xFF, nk);
        }

        if (u8 pk = nk - 1)
        {
            for (u8 i = k + 1; i != n; ++i)
            {
                r += std::min<u8>(tickets[i] & 0xFF, pk);
            }
        }

        return r;
    }
};
