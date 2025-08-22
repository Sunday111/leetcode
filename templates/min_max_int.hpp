#pragma once

#include <concepts>

#include "force_inline.hpp"
#include "hot_path.hpp"
#include "int_if.hpp"

template <std::integral T>
[[nodiscard]] FORCE_INLINE HOT_PATH constexpr T int_min(T a, T b) noexcept
{
    return iif(a < b, a, b);
}

template <std::integral T>
[[nodiscard]] FORCE_INLINE HOT_PATH constexpr T int_max(T a, T b) noexcept
{
    return iif(a > b, a, b);
}
