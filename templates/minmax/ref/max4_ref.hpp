#pragma once

#include "minmax/ref/max2_ref.hpp"

inline static constexpr auto max4_ref =
    []<typename T> [[gnu::always_inline, nodiscard]] (
        const T& a,
        const T& b,
        const T& c,
        const T& d) noexcept -> const T&
{
    return max2_ref(max2_ref(a, b), max2_ref(c, d));
};
