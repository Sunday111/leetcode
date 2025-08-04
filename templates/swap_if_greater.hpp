#pragma once

#include <concepts>

#include "int_if.hpp"

// Swaps a and b if a > b. Only for integers. Branchless
template <std::integral Int>
FORCE_INLINE static constexpr void swap_if_greater(Int& a, Int& b) noexcept
{
    Int cond = iif(a > b, ~Int{0}, Int{0});
    Int mask = (a ^ b) & cond;
    a ^= mask, b ^= mask;
}
