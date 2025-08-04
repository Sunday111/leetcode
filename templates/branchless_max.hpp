#pragma once

#include <concepts>

#include "force_inline.hpp"
#include "hot_path.hpp"

template <std::integral T>
[[nodiscard]] FORCE_INLINE HOT_PATH constexpr T branchless_max(
    T a,
    T b) noexcept
{
    T m = static_cast<T>(-T{a > b});
    return (m & a) | (~m & b);
}
