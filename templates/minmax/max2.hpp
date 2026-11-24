#pragma once

#include "int_if.hpp"

inline static constexpr auto max2 =
    []<typename T> [[gnu::always_inline, nodiscard]] (T a, T b) noexcept -> T
{
    if constexpr (std::integral<T>)
    {
        return iif(a < b, b, a);
    }
    else
    {
        return a < b ? b : a;
    }
};
