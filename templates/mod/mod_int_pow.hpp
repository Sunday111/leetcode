#pragma once

#include "mod/mod_int_mul.hpp"  // IWYU pragma: export

template <std::unsigned_integral Exp>
[[nodiscard, gnu::always_inline]] constexpr ModInt ModInt::pow(
    Exp exp) const noexcept
{
    ModInt r{1}, b = *this;

    while (exp)
    {
        // these two lines are equal to if (exp & 1) r *= b;
        u32 t = -(exp & 1);
        r *= ModInt((b.value & t) + (1u & ~t));

        b *= b;
        exp >>= 1;
    }

    return r;
}
