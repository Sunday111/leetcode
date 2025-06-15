#pragma once

#include <algorithm>
#include <array>
#include <cstdint>

using u8 = uint8_t;
using u32 = uint32_t;

struct Digits
{
    [[nodiscard]] static constexpr Digits fromInt(u32 v) noexcept
    {
        Digits r;
        r.initWith(v);
        return r;
    }

    constexpr void initWith(u32 v) noexcept
    {
        num = 0;
        for (; v; v /= 10)
        {
            digits[num++] = v % 10;
        }
        std::reverse(digits.begin(), std::next(digits.begin(), num));
    }

    [[nodiscard]] constexpr u8& operator[](u8 i) noexcept { return digits[i]; }
    [[nodiscard]] constexpr const u8& operator[](u8 i) const noexcept
    {
        return digits[i];
    }

    [[nodiscard]] constexpr u32 toInt() const noexcept
    {
        u32 v = 0;
        for (u8 i = 0; i != num; ++i)
        {
            v *= 10;
            v += digits[i];
        }

        return v;
    }

    constexpr void replaceDigit(u8 from, u8 to) noexcept
    {
        if (from != to)
        {
            for (u8 i = 0; i != num; ++i)
            {
                if (digits[i] == from)
                {
                    digits[i] = to;
                }
            }
        }
    }

    [[nodiscard]] constexpr Digits withReplacedDigits(u8 from, u8 to)
        const noexcept
    {
        auto r = *this;
        r.replaceDigit(from, to);
        return r;
    }

    // At most 10 digits for 32 bit value
    std::array<u8, 10> digits{};
    u8 num = 0;
};

class Solution
{
public:
    [[nodiscard]] static constexpr u32 maxDiff(u32 v) noexcept
    {
        const auto digits = Digits::fromInt(v);

        const u32 lowest = [&]
        {
            // Replace the most significant digit with one if it is not 1.
            if (const u8 msd = digits[0]; msd != 1)
            {
                return digits.withReplacedDigits(msd, 1).toInt();
            }

            // The most significant digit is one.
            // Try to replace others greater than 1 with zero.
            for (u8 i = 1; i != digits.num; ++i)
            {
                if (u8 digit = digits[i]; digit > 1)
                {
                    return digits.withReplacedDigits(digit, 0).toInt();
                }
            }

            // All digits are ones or zeroes. Nothing to do
            return v;
        }();

        const u32 highest = [&]
        {
            // Replace the most significant digit with 9 if it is not 9 already
            for (u8 i = 0; i != digits.num; ++i)
            {
                if (u8 digit = digits[i]; digit != 9)
                {
                    return digits.withReplacedDigits(digit, 9).toInt();
                }
            }

            // All digits are nines. Nothing to do
            return v;
        }();

        return highest - lowest;
    }
};
