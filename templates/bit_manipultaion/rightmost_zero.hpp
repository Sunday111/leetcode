#pragma once

#include <bit>
#include <concepts>

#include "force_inline.hpp"
#include "integral_aliases.hpp"

template <std::unsigned_integral T>
    requires(sizeof(T) < 32)
[[nodiscard]] FORCE_INLINE constexpr u8 rightmost_zero(T x) noexcept
{
    return std::countr_one(x) & 0xFF;
}
