#pragma once

#include "minmax/min2.hpp"

inline static constexpr auto min4 =
    []<typename T> [[gnu::always_inline, nodiscard]] (
        T a,
        T b,
        T c,
        T d) noexcept -> T
{
    return min2(min2(a, b), min2(c, d));
};
