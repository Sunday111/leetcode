#pragma once

#include "int_if.hpp"

inline static constexpr auto min2 =
    []<typename T> [[gnu::always_inline, nodiscard]] (T a, T b) noexcept -> T
{
    if constexpr (std::integral<T>)
    {
        return iif(b < a, b, a);
    }
    else
    {
        return b < a ? b : a;
    }
};
