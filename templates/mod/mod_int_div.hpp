#pragma once

#include "mod/mod_int_inv.hpp"  // IWYU pragma: export
#include "mod/mod_int_mul.hpp"  // IWYU pragma: export

[[gnu::always_inline]] constexpr ModInt& ModInt::operator/=(
    const ModInt& rhs) noexcept
{
    return *this *= rhs.inverse();
}

[[nodiscard, gnu::always_inline]] constexpr ModInt ModInt::operator/(
    const ModInt& rhs) const noexcept
{
    auto copy = *this;
    copy /= rhs;
    return copy;
}
