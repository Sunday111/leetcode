#pragma once

#include <concepts>

#include "force_inline.hpp"

template <std::integral T>
[[nodiscard]] FORCE_INLINE constexpr T iif(bool c, T a, T b) noexcept
{
    return (a & static_cast<T>(-c)) + (b & static_cast<T>(~static_cast<T>(-c)));
}
