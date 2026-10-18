#pragma once

#include <concepts>

#include "integral_aliases.hpp"

template <std::unsigned_integral T>
[[nodiscard, gnu::always_inline]] inline static constexpr T
clear_bit(T x, u8 i, bool condition = true) noexcept
{
    return x & ~(T{condition} << i);
}
