#pragma once

#include <algorithm>

inline static constexpr auto max2 =
    []<typename T> [[gnu::always_inline, nodiscard]] (
        const T& a,
        const T& b) noexcept -> const T&
{
    return std::max(a, b);
};
