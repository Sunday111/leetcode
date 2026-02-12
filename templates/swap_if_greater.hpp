#pragma once

#include <concepts>

#include "force_inline.hpp"
#include "swap_if.hpp"

// Swaps a and b if a > b. Only for integers. Branchless
template <std::integral Int>
FORCE_INLINE static constexpr void swap_if_greater(Int& a, Int& b) noexcept
{
    swap_if(a > b, a, b);
}
