#pragma once

#include <type_traits>

#include "force_inline.hpp"

// simplified std::exchange
template <typename T>
    requires std::is_trivially_copyable_v<T>
[[nodiscard]] FORCE_INLINE constexpr T exch(T& x, T new_value) noexcept
{
    T tmp = x;
    x = new_value;
    return tmp;
}
