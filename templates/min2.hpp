#pragma once

#include <algorithm>

inline static constexpr auto min2 =
    []<typename T> [[gnu::always_inline]] (const T& a, const T& b) -> const T&
{
    return std::min(a, b);
};
