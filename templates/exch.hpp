#pragma once

#include <concepts>

#include "force_inline.hpp"

// simplified std::exchange
template <std::integral T>
[[nodiscard]] FORCE_INLINE constexpr T exch(T& x, T new_value) noexcept
{
    T tmp = x;
    x = new_value;
    return tmp;
}
