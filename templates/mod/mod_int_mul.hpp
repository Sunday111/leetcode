#pragma once

#include "cast.hpp"
#include "mod/mod_int.hpp"  // IWYU pragma: export

[[gnu::always_inline]] constexpr ModInt& operator*=(
    ModInt& lhs,
    const ModInt& rhs) noexcept
{
    u64 v = rhs.value;
    v *= lhs.value;
    if (v >= kMOD) v %= kMOD;
    lhs.value = cast<u32>(v);
    return lhs;
}

[[nodiscard, gnu::always_inline]] constexpr ModInt operator*(
    ModInt lhs,
    const ModInt& rhs) noexcept
{
    lhs *= rhs;
    return lhs;
}
