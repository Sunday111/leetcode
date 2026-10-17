#pragma once

#include "mod/mod_int_inv.hpp"  // IWYU pragma: export
#include "mod/mod_int_mul.hpp"  // IWYU pragma: export

[[gnu::always_inline]] constexpr ModInt& operator/=(
    ModInt& lhs,
    const ModInt& rhs) noexcept
{
    lhs *= inverse(rhs);
    return lhs;
}

[[nodiscard, gnu::always_inline]] constexpr ModInt operator/(
    ModInt lhs,
    const ModInt& rhs) noexcept
{
    lhs /= rhs;
    return lhs;
}
