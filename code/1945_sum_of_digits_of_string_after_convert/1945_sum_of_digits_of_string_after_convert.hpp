#pragma once

#include <string_view>

class Solution
{
public:
    using u16 = uint16_t;
    using u8 = uint8_t;
    [[nodiscard]] static constexpr u16 getLucky(
        std::string_view s,
        u8 k) noexcept
    {
        constexpr char p = 'a' - 1;
        u16 v = 0;
        for (char c : s)
        {
            u8 t = (c - p) & 0xFF;
            v += t % 10;
            t /= 10;
            v += t % 10;
        }

        while (v > 9 && --k > 0)
        {
            for (auto t = std::exchange(v, 0); t; t /= 10)
            {
                v += t % 10;
            }
        }

        return v;
    }
};
