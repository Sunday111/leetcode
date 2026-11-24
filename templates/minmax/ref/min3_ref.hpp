#pragma once

#include "minmax/ref/min2_ref.hpp"

inline static constexpr auto min3_ref =
    []<typename T> [[gnu::always_inline, nodiscard]] (
        const T& a,
        const T& b,
        const T& c) noexcept -> const T&
{
    return min2_ref(min2_ref(a, b), c);
};
