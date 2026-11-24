#pragma once

#include "minmax/ref/max2_ref.hpp"

inline static constexpr auto max3_ref =
    []<typename T> [[gnu::always_inline, nodiscard]] (
        const T& a,
        const T& b,
        const T& c) noexcept -> const T&
{
    return max2_ref(max2_ref(a, b), c);
};
