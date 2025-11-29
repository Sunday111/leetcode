#pragma once

#include <concepts>

#include "cast.hpp"
#include "force_inline.hpp"

template <std::integral T>
[[nodiscard]] FORCE_INLINE constexpr T iif(bool c, T a, T b) noexcept
{
    return (a & cast<T>(-c)) + (b & cast<T>(~cast<T>(-c)));
}
