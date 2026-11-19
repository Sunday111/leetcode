#pragma once

#include <bit>
#include <cstdint>

class Solution
{
public:
    using i64 = int64_t;
    using u64 = uint64_t;
    [[nodiscard]] static constexpr i64 makeTheIntegerZero(
        i64 num1,
        i64 num2) noexcept
    {
        for (i64 x = 1, t = num1 - num2; x != 61; ++x, t -= num2)
        {
            if (std::popcount(std::bit_cast<u64>(t)) <= x && x <= t)
            {
                return x;
            }
        }

        return -1;
    }
};
