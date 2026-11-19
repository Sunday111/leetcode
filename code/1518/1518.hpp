#pragma once

#include <cstdint>

class Solution
{
public:
    using u8 = uint8_t;
    [[nodiscard]] static constexpr int numWaterBottles(
        u8 full,
        u8 exchange) noexcept
    {
        u8 drank = 0, empty = 0;

        while (full)
        {
            while (full)
            {
                drank += full;
                empty += full % exchange;
                full /= exchange;
            }

            full = empty / exchange;
            empty %= exchange;
        }

        return drank;
    }
};
