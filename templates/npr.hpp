#pragma once

#include "force_inline.hpp"
#include "integral_aliases.hpp"

[[nodiscard]] FORCE_INLINE constexpr u64 npr(u8 n, u8 r) noexcept
{
    if (r > n) return 0;

    u64 res = 1;
    for (u32 i = 0; i != r; ++i)
    {
        res *= u64{n - i};
    }
    return res;
}

static_assert(npr(20, 4) == 116280);
