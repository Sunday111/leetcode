#pragma once

#include <bit>
#include <concepts>
#include <type_traits>

#include "force_inline.hpp"
#include "hot_path.hpp"

template <std::integral T>
[[nodiscard]] FORCE_INLINE HOT_PATH constexpr T iif(bool c, T a, T b) noexcept
{
    return (a & static_cast<T>(-c)) + (b & static_cast<T>(~static_cast<T>(-c)));
}

template <typename T>
    requires(std::is_pointer_v<T>)
[[nodiscard]] FORCE_INLINE HOT_PATH constexpr T iif(bool c, T a, T b) noexcept
{
    return std::bit_cast<T>(
        iif(c, std::bit_cast<std::size_t>(a), std::bit_cast<std::size_t>(b)));
}

template <std::integral T>
[[nodiscard]] FORCE_INLINE HOT_PATH constexpr T negate_if(bool c, T v) noexcept
{
    return iif(c, -v, v);
}
