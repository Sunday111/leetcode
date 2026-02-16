#pragma once

#include "force_inline.hpp"
#include "integral_aliases.hpp"

// This is safe for n < 68
[[nodiscard]] FORCE_INLINE constexpr u64 ncr(u8 n, u8 r) noexcept
{
    if (r > n) return 0;
    if (r > n - r) r = n - r;

    u64 res = 1;
    for (u32 i = 1, k = n - r + i; i <= r; ++i, ++k)
    {
        res *= k;
        res /= i;
    }
    return res;
}
