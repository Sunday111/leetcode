#pragma once

#include <vector>

class Solution
{
public:
    using u8 = uint8_t;
    using u16 = uint16_t;
    [[nodiscard]] static constexpr bool no_zero_digits(u16 v) noexcept
    {
        u8 d0 = v % 10 != 0;
        u8 d1 = (v / 10) % 10 != 0;
        u8 d2 = (v / 100) % 10 != 0;
        u8 d3 = v <= 1000;
        return d0 & ((d1 & d2) | (~d2 & d3));
    }

    [[nodiscard]] static constexpr std::vector<int> getNoZeroIntegers(
        int v) noexcept
    {
        for (int a : {1, 2, 11, 111, 22, 21, 212, 222})
        {
            if (int b = v - a; no_zero_digits(b & 0xFFFF)) return {a, b};
        }

        std::unreachable();
    }
};
