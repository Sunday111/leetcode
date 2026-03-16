#pragma once

#include <concepts>

// Swaps a and b if condition is true. Only for integers. Branchless
inline static constexpr auto swap_if =
    []<std::integral Int> [[gnu::always_inline]] (
        bool condition,
        Int& a,
        Int& b) noexcept
{
    Int mask = static_cast<Int>(static_cast<Int>(a ^ b) & -Int{condition});
    a ^= mask, b ^= mask;
};
