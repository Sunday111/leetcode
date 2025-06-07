#pragma once

#include <bit>
#include <cassert>

// 1 2 3 4 5 6 7 8 9101112131415
// 0                               n = 1, s =  1,
// 0 1 1                           n = 2, s =  3, p = 2
// 0 1 1 1 0 0 1                   n = 3, s =  7, p = 4
// 0 1 1 1 0 0 1 1 0 1 1 0 0 0 1   n = 4, s = 15, p = 8

class Solution
{
public:
    using u32 = uint32_t;
    [[nodiscard]] static constexpr bool findKthBitR(u32 k) noexcept
    {
        if (k == 1) return false;

        u32 p = 1 << (31 - std::countl_zero(k));
        if (k == p) return true;
        if (k < p) return findKthBitR(k);
        return !findKthBitR(2 * p - k);
    }

    [[nodiscard]] static constexpr char findKthBit(
        [[maybe_unused]] int n,
        u32 k) noexcept
    {
        return findKthBitR(k) ? '1' : '0';
    }
};
