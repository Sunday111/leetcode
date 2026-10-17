#pragma once

#include "cast.hpp"
#include "mod/mod_int.hpp"  // IWYU pragma: export

[[gnu::always_inline]] constexpr ModInt& ModInt::operator*=(
    const ModInt& rhs) noexcept
{
    u64 v = rhs.value;
    v *= value;
    if (v >= kMOD) v %= kMOD;
    value = cast<u32>(v);
    return *this;
}

[[nodiscard, gnu::always_inline]] constexpr ModInt ModInt::operator*(
    const ModInt& rhs) const noexcept
{
    auto copy = *this;
    copy *= rhs;
    return copy;
}
