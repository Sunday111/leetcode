#pragma once

#include "mod/mod_int.hpp"  // IWYU pragma: export

[[nodiscard, gnu::always_inline]] constexpr ModInt inverse(ModInt x) noexcept
{
    auto a = x.value;
    u32 x0 = 1, x1 = 0, mod = kMOD;
    while (a)
    {
        u32 q = mod / a;
        u32 r = mod % a;
        u32 x2 = x1 - q * x0;
        mod = a;
        a = r;
        x1 = x0;
        x0 = x2;
    }
    return {(x1 + kMOD) % kMOD};
}
