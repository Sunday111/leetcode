#pragma once

#include <concepts>
#include <type_traits>

#include "force_inline.hpp"

template <std::integral T>
[[nodiscard]] FORCE_INLINE static constexpr T ceil_div(
    T a,
    std::type_identity_t<T> b) noexcept
{
    return (a + (b - 1)) / b;
}
