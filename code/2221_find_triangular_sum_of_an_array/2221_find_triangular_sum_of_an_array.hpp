#pragma once

#include <array>
#include <cstdint>
#include <vector>

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;

#define FORCE_INLINE inline __attribute__((always_inline))

class BinomialMod10
{
public:
    static constexpr std::array<std::array<u8, 5>, 5> kMod5Table = []()
    {
        std::array<std::array<u8, 5>, 5> table{};

        for (u8 a = 0; a != 5; ++a)
        {
            for (u8 b = 0; b <= a; ++b)
            {
                u32 num = 1, den = 1;
                for (u32 i = 0; i < b; ++i)
                {
                    num *= (a - i);
                    den *= (i + 1);
                }
                table[a][b] = (num / den) % 5;
            }
        }
        return table;
    }();

    // Compute C(n, k) % 2 using bitwise logic
    [[nodiscard]] FORCE_INLINE static constexpr u8 binom_mod2(
        u16 n,
        u16 k) noexcept
    {
        return ((k & ~n) == 0) ? 1 : 0;
    }

    // Compute C(n, k) % 5 using Lucas's theorem and constexpr table
    [[nodiscard]] FORCE_INLINE static constexpr u8 binom_mod5(
        u32 n,
        u32 k) noexcept
    {
        u8 result = 1;
        while (n > 0 || k > 0)
        {
            u32 ni = n % 5, ki = k % 5;
            if (ki > ni) return 0;
            result = (result * kMod5Table[ni][ki]) % 5;
            n /= 5, k /= 5;
        }
        return result;
    }

    // Combine mod 2 and mod 5 using brute-force CRT
    [[nodiscard]] FORCE_INLINE static constexpr u8 crt_mod10(
        u16 mod2,
        u16 mod5) noexcept
    {
        u8 x = 0;
        while (x % 2 != mod2 || x % 5 != mod5) ++x;
        return x;
    }

    // Final C(n, k) % 10 using mod2, mod5, and CRT
    [[nodiscard]] FORCE_INLINE static constexpr u8 binom_mod10(
        u16 n,
        u16 k) noexcept
    {
        return crt_mod10(binom_mod2(n, k), binom_mod5(n, k));
    }
};

class Solution
{
public:
    [[nodiscard]] static constexpr u32 triangularSum(
        const std::vector<int>& nums) noexcept
    {
        u16 r = 0, n = static_cast<u16>(nums.size()), p = n - 1;
        for (u16 i = 0; i != n; ++i)
        {
            r += static_cast<u32>(nums[i]) * BinomialMod10::binom_mod10(p, i);
        }

        return r % 10;
    }
};
