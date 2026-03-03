#pragma once

#include <concepts>

#include "force_inline.hpp"
#include "integral_aliases.hpp"

template <std::unsigned_integral T>
[[nodiscard]] FORCE_INLINE static constexpr T
clear_bit(T x, u8 i, bool condition = true) noexcept
{
    return x & ~(T{condition} << i);
}
