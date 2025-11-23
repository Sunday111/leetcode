#pragma once

#include <array>

#include "swap_if_greater.hpp"

template <std::integral Int, size_t n>
FORCE_INLINE static constexpr void update_minima(
    Int x,
    std::array<Int, n>& vals) noexcept
{
#pragma GCC unroll
    for (auto& v : vals) swap_if_greater(v, x);
}
