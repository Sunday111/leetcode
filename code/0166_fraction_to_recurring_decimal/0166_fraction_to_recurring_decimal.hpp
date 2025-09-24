#pragma once

#include <algorithm>
#include <cstdlib>
#include <numeric>
#include <string>

class Solution
{
public:
    using u8 = uint8_t;
    using u32 = uint32_t;
    using u64 = uint64_t;
    static constexpr std::string fractionToDecimal(
        const int64_t a_,
        const int64_t b_) noexcept
    {
        const auto a = static_cast<u64>(std::abs(a_));
        const auto b = static_cast<u64>(std::abs(b_));

        std::string result;

        // Integral part (reversed)
        {
            u64 q = a / b;
            do
            {
                result += static_cast<char>((q % 10) + '0');
                q /= 10;
            } while (q);
        }

        // Sign.
        if (a_ && ((a_ < 0) ^ (b_ < 0))) result.push_back('-');

        std::ranges::reverse(result);

        // Fractional part.
        if (u64 r = a % b; r != 0)
        {
            result.push_back('.');

            u32 m = 0, n = 0;
            u64 d = b / std::gcd(a, b);
            while (d % 2 == 0)
            {
                d /= 2;
                ++m;
            }
            while (d % 5 == 0)
            {
                d /= 5;
                ++n;
            }

            // Write non-repeating part.
            const u32 l1 = std::max(m, n);
            for (u32 p = 0; p != l1; p++)
            {
                r *= 10;
                result += static_cast<char>(r / b + '0');
                r = r % b;
            }

            // Write reptend. It will exist if denominator has
            // prime factors other than 2 or 5.
            if (d != 1)
            {
                u32 l2 = 0;  // reptend length
                ++l2;
                for (u64 t = 10 % d; t != 1;)
                {
                    t = (t * 10) % d;
                    ++l2;
                }

                result += '(';

                for (u32 p = 0; p != l2; p++)
                {
                    r *= 10;
                    result += static_cast<char>(r / b + '0');
                    r = r % b;
                }

                result += ')';
            }
        }

        return result;
    }
};
