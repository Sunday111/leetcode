#pragma once

#include <type_traits>

// simplified std::exchange
template <typename T>
    requires std::is_trivially_copyable_v<T>
[[nodiscard, gnu::always_inline]] constexpr T exch(T& x, T new_value) noexcept
{
    T tmp = x;
    x = new_value;
    return tmp;
}
