#pragma once

#include "integral_aliases.hpp"
#include "next_with_same_popcount.hpp"
#include "with_bmi2.hpp"

// Returns value >= v such that popcount(value) == x
[[nodiscard]] FORCE_INLINE WITH_BMI2 u32
next_with_x_popcount(u32 v, u8 x) noexcept
{
    u32 vp = std::popcount(v) & 0xFF;
    if (vp == x) return v;

    if (vp < x)
    {
        u32 need = x - vp;
        u32 add = _pdep_u32((1u << need) - 1, ~v);
        return v | add;
    }

    u32 dense = _pext_u32(v, ~u32{});
    dense = _pext_u32(~u32{}, v);
    dense &= ~((1u << (vp - x)) - 1);
    u32 tmp = _pdep_u32(dense, v);
    if (tmp >= v) return tmp;
    return next_with_same_popcount(tmp);
}
