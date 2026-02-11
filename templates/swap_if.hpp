#pragma once

#include <concepts>

#include "force_inline.hpp"

// Swaps a and b if condition is true. Only for integers. Branchless
template <std::integral Int>
FORCE_INLINE static constexpr void
swap_if(bool condition, Int& a, Int& b) noexcept
{
    Int mask = static_cast<Int>(static_cast<Int>(a ^ b) & -Int{condition});
    a ^= mask, b ^= mask;
}
