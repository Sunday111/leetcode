#pragma once

#include "force_inline.hpp"
#include "integral_aliases.hpp"

FORCE_INLINE constexpr u32 reverse32(u32 x) noexcept
{
    x = ((x & 0x55555555) << 1) | ((x >> 1) & 0x55555555);
    x = ((x & 0x33333333) << 2) | ((x >> 2) & 0x33333333);
    x = ((x & 0x0F0F0F0F) << 4) | ((x >> 4) & 0x0F0F0F0F);
    return __builtin_bswap32(x);
}
