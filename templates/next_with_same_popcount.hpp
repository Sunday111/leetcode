#pragma once

#include <bit>
#include <concepts>

#include "force_inline.hpp"

/* This is an implementation of Gosper's hack, which is an efficient method of
 * computing the next higher integer with the same number of set bits (popcout,
 * hamming weight)
 */
template <std::unsigned_integral T>
[[nodiscard]] FORCE_INLINE constexpr T next_with_same_popcount(T q) noexcept
{
    T r = q & -q;
    T n = q + r;
    q = (((n ^ q) >> 2) >> std::countr_zero(q)) | n;
    return q;
}
