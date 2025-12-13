#pragma once

#include <algorithm>
#include <cmath>

#include "integral_aliases.hpp"

class Solution
{
private:
    static constexpr u32 max_len(u64 s) noexcept
    {
        return static_cast<u32>(
            std::ceil(std::sqrt(1 + 8 * static_cast<double>(s)) / 2));
    }

    static constexpr bool try_solve(u64 k, u64 s) noexcept
    {
        u64 t1 = 2 * s, t2 = (k - 1) * k;
        if (t1 <= t2) return false;
        t1 -= t2;
        if (t1 % k) return false;
        t1 /= k;
        return (t1 % 2) == 0;
    }

public:
    static constexpr u32 consecutiveNumbersSum(u32 s) noexcept
    {
        u32 r = 1;
        for (u32 k = std::max<u32>(max_len(s), 2u); k != 1; --k)
        {
            r += try_solve(k, s);
        }
        return r;
    }
};
