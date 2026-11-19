#pragma once

#include <cstdint>

class Solution
{
public:
    using u16 = uint16_t;

    [[nodiscard]] static constexpr u16 reinitializePermutation(u16 n) noexcept
    {
        u16 r = 0, i = 1;
        --n;
        do
        {
            i *= 2;
            i %= n;
            r++;
        } while (i > 1);

        return r;
    }
};
