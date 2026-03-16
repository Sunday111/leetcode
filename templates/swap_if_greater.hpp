#pragma once

#include <concepts>

#include "swap_if.hpp"

// Swaps a and b if a > b. Only for integers. Branchless
inline static constexpr auto swap_if_greater =
    []<std::integral Int> [[gnu::always_inline]] (Int & a, Int& b) noexcept
{
    swap_if(a > b, a, b);
};
