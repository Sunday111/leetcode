#pragma once

#include <concepts>

#include "mod/mod_int_mul.hpp"  // IWYU pragma: export

template <std::unsigned_integral Exp>
[[nodiscard, gnu::always_inline]] constexpr ModInt pow(
    ModInt b,
    Exp exp) noexcept
{
    ModInt r{1};

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
