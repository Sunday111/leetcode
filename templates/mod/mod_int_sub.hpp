#pragma once

#include "mod/mod_int.hpp"  // IWYU pragma: export

[[gnu::always_inline]] constexpr ModInt& ModInt::operator-=(
    const ModInt& rhs) noexcept
{
    value += kMOD & -u32{value < rhs.value};
    value -= rhs.value;
    return *this;
}

[[nodiscard, gnu::always_inline]] constexpr ModInt ModInt::operator-(
    const ModInt& rhs) const noexcept
{
    auto copy = *this;
    copy -= rhs;
    return copy;
}
