#pragma once

#include <concepts>

#include "force_inline.hpp"

template <std::integral T>
[[nodiscard]] FORCE_INLINE static constexpr T ceil_div(T a, T b) noexcept
{
    return (a + (b - 1)) / b;
}
