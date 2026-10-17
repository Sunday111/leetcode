#pragma once

#include "mod/mod_int.hpp"  // IWYU pragma: export

[[gnu::always_inline]] constexpr ModInt& operator+=(
    ModInt& lhs,
    const ModInt& rhs) noexcept
{
    lhs.value += rhs.value;
    lhs.value -= kMOD & -u32{lhs.value >= kMOD};
    return lhs;
}

[[nodiscard, gnu::always_inline]] constexpr ModInt operator+(
    ModInt lhs,
    const ModInt& rhs) noexcept
{
    lhs += rhs;
    return lhs;
}
