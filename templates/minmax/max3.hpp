#pragma once

#include "minmax/max2.hpp"

inline static constexpr auto max3 =
    []<typename T> [[gnu::always_inline, nodiscard]] (T a, T b, T c) noexcept
    -> T
{
    return max2(max2(a, b), c);
};
