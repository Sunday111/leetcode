#pragma once

#include <concepts>

#include "force_inline.hpp"
#include "integral_aliases.hpp"

template <std::unsigned_integral T>
[[nodiscard]] FORCE_INLINE static constexpr T clearBit(T x, u8 i) noexcept
{
    return x & ~(T{1} << i);
}
