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
        if (a_ && ((a_ < 0) ^ (b_ < 0))) result += '-';

        std::ranges::reverse(result);

        // Fractional part.
        if (u64 r = a % b; r != 0)
        {
            result.push_back('.');

            auto write_digit = [&]()
            {
                r *= 10;
                result += static_cast<char>(r / b + '0');
                r = r % b;
            };

            u64 d = b / std::gcd(a, b);

            // Write non-repeating part.
            for (; d % 10 == 0; d /= 10) write_digit();
            for (; d % 5 == 0; d /= 5) write_digit();
            for (; d % 2 == 0; d /= 2) write_digit();

            // Write reptend. It will exist if denominator has
            // prime factors other than 2 or 5 (removed above).
            if (d != 1)
            {
                result += '(';
                for (u64 t = 10 % d; t != 1; t = (t * 10) % d) write_digit();
                write_digit();
                result += ')';
            }
        }

        return result;
    }
};
