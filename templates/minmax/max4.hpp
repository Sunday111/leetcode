#pragma once

#include "minmax/max2.hpp"

inline static constexpr auto max4 =
    []<typename T> [[gnu::always_inline, nodiscard]] (
        T a,
        T b,
        T c,
        T d) noexcept -> T
{
    return max2(max2(a, b), max2(c, d));
};
