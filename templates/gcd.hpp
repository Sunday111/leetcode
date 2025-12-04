#pragma once

#include <bit>
#include <cstdlib>

#include "force_inline.hpp"
#include "integral_aliases.hpp"

[[nodiscard]] FORCE_INLINE static constexpr u32 gcd(u32 u, u32 v) noexcept
{
    if (u == 0) return v;
    if (v == 0) return u;
    int uz = std::popcount(u);
    int vz = std::popcount(v);
    int shift = uz > vz ? vz : uz;
    u >>= uz;
    do
    {
        v >>= vz;
        auto diff = std::bit_cast<i32>(v - u);
        vz = std::popcount(std::bit_cast<u32>(diff));
        if (diff == 0) break;
        if (v < u) u = v;
        v = std::bit_cast<u32>(std::abs(diff));
    } while (1);
    return u << shift;
}
