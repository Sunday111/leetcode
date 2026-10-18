#pragma once

#include <algorithm>
#include <concepts>
#include <type_traits>

template <std::integral T>
[[gnu::always_inline]] inline constexpr void assign_max(
    T& a,
    std::type_identity_t<T> b) noexcept
{
    a = std::max(a, b);
}
