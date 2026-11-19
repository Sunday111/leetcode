#pragma once

#include <cstdint>

class Solution
{
public:
    using u32 = uint32_t;

    [[nodiscard]] static constexpr u32 replaceDigit(u32 v, u32 from, u32 to)
    {
        if (from != to)
        {
            for (u32 m = 1; v / m; m *= 10)
            {
                u32 digit = (v / m) % 10;
                if (digit == from)
                {
                    v -= from * m;
                    v += to * m;
                }
            }
        }

        return v;
    }

    [[nodiscard]] static constexpr u32 minMaxDifference(const u32 num) noexcept
    {
        const u32 highest = [&]
        {
            // gonna find most significant digit that is not 9
            // and replace it with 9
            u32 digit_to_replace = num % 10;
            for (u32 v = num; v; v /= 10)
            {
                u32 digit = v % 10;
                if (digit != 9)
                {
                    digit_to_replace = digit;
                }
            }

            return replaceDigit(num, digit_to_replace, 9);
        }();

        const u32 lowest = [&]
        {
            // gonna find most significant digit
            // and replace it with zero
            u32 digit_to_replace = num;
            while (digit_to_replace > 9) digit_to_replace /= 10;
            return replaceDigit(num, digit_to_replace, 0);
        }();

        return highest - lowest;
    }
};
