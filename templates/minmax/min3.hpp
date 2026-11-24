#pragma once

#include "minmax/min2.hpp"

inline static constexpr auto min3 =
    []<typename T> [[gnu::always_inline, nodiscard]] (T a, T b, T c) noexcept
    -> T
{
    return min2(min2(a, b), c);
};
