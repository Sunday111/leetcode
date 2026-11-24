#pragma once

#include "minmax/ref/min2_ref.hpp"

inline static constexpr auto min4_ref =
    []<typename T> [[gnu::always_inline, nodiscard]] (
        const T& a,
        const T& b,
        const T& c,
        const T& d) noexcept -> const T&
{
    return min2_ref(min2_ref(a, b), min2_ref(c, d));
};
