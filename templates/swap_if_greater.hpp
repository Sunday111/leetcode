#pragma once

#include <concepts>

#include "force_inline.hpp"

// Swaps a and b if a > b. Only for integers. Branchless
template <std::integral Int>
FORCE_INLINE static constexpr void swap_if_greater(Int& a, Int& b) noexcept
{
    Int mask = (a ^ b) & -Int{a > b};
    a ^= mask, b ^= mask;
}
