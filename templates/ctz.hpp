#pragma once

#include <concepts>

#include "integral_aliases.hpp"

// x must be nonzero.
template <std::unsigned_integral T>
    requires(sizeof(T) <= sizeof(u64))
[[nodiscard, gnu::always_inline]] constexpr u8 ctz(T x) noexcept
{
    if constexpr (sizeof(T) <= sizeof(u32))
    {
        return __builtin_ctz(x) & 31;
    }
    else
    {
        return __builtin_ctzll(x) & 63;
    }
}
