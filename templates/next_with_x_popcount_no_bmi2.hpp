#pragma once

#include "force_inline.hpp"
#include "integral_aliases.hpp"
#include "next_with_same_popcount.hpp"

// generates value >= v with exactly x bits set

[[nodiscard]] FORCE_INLINE constexpr u32 next_with_x_popcount(u32 v, u8 x)
{
    auto vp = std::popcount(v);
    if (vp == x) return v;

    if (vp < x)
    {
        // v has less bits than required - need to set lsb
        // v = 10000100000, x = 3, r = 10000100001
        u32 mask = 1u;
        while (vp != x)
        {
            vp += !(v & mask);
            v |= mask;
            mask <<= 1;
        }

        return v;
    }
    else
    {
        // v has more bits than required - need to clear some lsb
        // and use gospers hack on the result
        // v = 10001000100, x = 2, r = gospers_hack(10001000000)

        while (vp != x)
        {
            v &= ~(1u << std::countr_zero(v));
            --vp;
        }

        return next_with_same_popcount(v);
    }
}
static_assert(next_with_x_popcount(1, 1) == 1);
static_assert(next_with_x_popcount(0b1001001, 4) == 0b1001011);
static_assert(next_with_x_popcount(0b1001011, 3) == 0b1001100);
static_assert(next_with_x_popcount(0b10011100, 2) == 0b10100000);
