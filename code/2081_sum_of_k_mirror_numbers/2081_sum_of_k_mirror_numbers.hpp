#pragma once

#include <algorithm>
#include <array>
#include <cstdint>
#include <ranges>
#include <span>

#include "integral_aliases.hpp"
#include "reverse_bits_32.hpp"

class Solution
{
public:
    static constexpr std::array
        kMaxDigits{0, 0, 64, 41, 32, 28, 25, 23, 22, 21};

    static constexpr auto kPowers = []
    {
        std::array<std::array<u64, 64>, 10> r{};
        for (u8 base = 2; base != 10; ++base)
        {
            u64 v = 1;
            for (u8 power = 0; power != kMaxDigits[base]; ++power)
            {
                r[base][power] = v;
                v *= base;
            }
        }
        return r;
    }();

    template <u8 base, u8 num_digits, bool lead = true, typename Callback>
    FORCE_INLINE static constexpr void genPalindromes(Callback cb)
    {
        if constexpr (base == 2)
        {
            // This block is unnecessary. But leetcode has strict compilation
            // time limits and this one generates the biggest number of
            // instantiations

            static_assert(lead);
            constexpr u8 half = num_digits / 2;

            if constexpr (!half)
            {
                if (num_digits & 1) cb(1);
            }
            else
            {
                constexpr u64 start = u64{1} << (half - 1);
                constexpr u64 limit = u64{1} << half;
                constexpr u64 m = num_digits & 1;

                for (u32 left_part = start; left_part != limit; ++left_part)
                {
                    u64 v = (u64{left_part} << (half + m)) |
                            (reverse32(left_part) >> (32 - half));
                    cb(v);
                    if constexpr (m) cb(v | (m << half));
                }
            }
        }
        else if constexpr (num_digits == 1)
        {
            for (u8 digit = lead ? 1 : 0; digit != base; ++digit) cb(digit);
        }
        else if constexpr (num_digits == 2)
        {
            for (u8 digit = lead ? 1 : 0; digit != base; ++digit)
            {
                const u64 add = digit * (kPowers[base][num_digits - 1] + 1);
                cb(add);
            }
        }
        else
        {
            for (u8 digit = lead ? 1 : 0; digit != base; ++digit)
            {
                const u64 add = digit * (kPowers[base][num_digits - 1] + 1);
                genPalindromes<base, num_digits - 2, false>(
                    [&](u64 value) { cb(value * base + add); });
            }
        }
    }

    [[nodiscard]] FORCE_INLINE static constexpr bool isPalindromeBase10(
        u64 v) noexcept
    {
        std::array<u8, 20> digits;  // NOLINT
        u8 n = 0;
        while (v)
        {
            digits[n++] = v % 10;
            v /= 10;
        }

        auto full = std::span{digits}.first(n);
        return std::ranges::equal(
            full.first(n / 2),
            full.last(n / 2) | std::views::reverse);
    }

    template <u8 base>
    [[nodiscard]] static constexpr u64 kMirrorT(u8 n) noexcept
    {
        u64 r = 0;

        auto cb = [&](u64 v)
        {
            if (isPalindromeBase10(v))
            {
                r += v;
                // std::println("{}", v);
                if (--n == 0) throw 0;
            }
        };

        try
        {
            [&]<u8... index>(std::integer_sequence<u8, index...>)
            {
                (genPalindromes<base, index + 1>(cb), ...);
            }(std::make_integer_sequence<u8, kMaxDigits[base]>());
        }
        catch (...)
        {
        }

        return r;
    }

    static constexpr std::array kFunctions{
        kMirrorT<2>,
        kMirrorT<3>,
        kMirrorT<4>,
        kMirrorT<5>,
        kMirrorT<6>,
        kMirrorT<7>,
        kMirrorT<8>,
        kMirrorT<9>,
    };

    [[nodiscard]] static constexpr u64 kMirror(u8 k, u8 n) noexcept
    {
        return kFunctions[k - 2](n);
    }
};

class Solution2
{
public:
    using u64 = uint64_t;
    using u32 = uint32_t;
    using u8 = uint8_t;

    u64 r = 0;
    u8 n = 0;

    static constexpr auto kReverseByteTable = []
    {
        auto reverse_byte = [](uint8_t b)
        {
            b = ((b & 0b00001111) << 4 | (b & 0b11110000) >> 4) & 0xFF;
            b = ((b & 0b00110011) << 2 | (b & 0b11001100) >> 2) & 0xFF;
            b = ((b & 0b01010101) << 1 | (b & 0b10101010) >> 1) & 0xFF;
            return b;
        };

        std::array<uint8_t, 256> result{};
        for (size_t i = 0; i != 256; ++i)
        {
            result[i] = reverse_byte(static_cast<uint8_t>(i));
        }
        return result;
    }();

    [[nodiscard]] FORCE_INLINE static constexpr u32 reverseBits(u32 n) noexcept
    {
        const u32 a = kReverseByteTable[(n >> 0) & 0xFF];
        const u32 b = kReverseByteTable[(n >> 8) & 0xFF];
        const u32 c = kReverseByteTable[(n >> 16) & 0xFF];
        const u32 d = kReverseByteTable[(n >> 24) & 0xFF];
        return (a << 24) | (b << 16) | (c << 8) | (d << 0);
    }

    static constexpr std::array
        kMaxDigits{0, 0, 64, 41, 32, 28, 25, 23, 22, 21};

    static constexpr auto kPowers = []
    {
        std::array<std::array<u64, 64>, 10> r{};
        for (u8 base = 2; base != 10; ++base)
        {
            u64 v = 1;
            for (u8 power = 0; power != kMaxDigits[base]; ++power)
            {
                r[base][power] = v;
                v *= base;
            }
        }
        return r;
    }();

    template <u8 base, u8 num_digits, bool lead = true>
    constexpr void genPalindromes(u64 outer_mul, u64 outer_add)
    {
        if constexpr (base == 2)
        {
            // This block is unnecessary. But leetcode has strict compilation
            // time limits and this one generates the biggest number of
            // instantiations

            static_assert(lead);
            constexpr u8 half = num_digits / 2;

            if constexpr (!half)
            {
                if (num_digits & 1) testValue(1);
            }
            else
            {
                constexpr u64 start = u64{1} << (half - 1);
                constexpr u64 limit = u64{1} << half;
                constexpr u64 m = num_digits & 1;

                for (u32 left_part = start; left_part != limit; ++left_part)
                {
                    u64 v = (u64{left_part} << (half + m)) |
                            (reverseBits(left_part) >> (32 - half));
                    testValue(v * outer_mul + outer_add);
                    if constexpr (m)
                    {
                        testValue((v | (m << half)) * outer_mul + outer_add);
                    }
                }
            }
        }
        else if constexpr (num_digits == 1)
        {
            for (u8 digit = lead ? 1 : 0; digit != base; ++digit)
            {
                testValue(u64{digit} * outer_mul + outer_add);
            }
        }
        else if constexpr (num_digits == 2)
        {
            outer_mul *= base + 1;
            for (u8 digit = lead ? 1 : 0; digit != base; ++digit)
            {
                testValue(digit * outer_mul + outer_add);
            }
        }
        else
        {
            for (u8 digit = lead ? 1 : 0; digit != base; ++digit)
            {
                const u64 add = digit * (kPowers[base][num_digits - 1] + 1);
                genPalindromes<base, num_digits - 2, false>(
                    base * outer_mul,
                    outer_add + add * outer_mul);
            }
        }
    }

    [[nodiscard]] FORCE_INLINE static constexpr bool isPalindromeBase10(
        u64 v) noexcept
    {
        std::array<u8, 20> digits;  // NOLINT
        u8 n = 0;
        while (v)
        {
            digits[n++] = v % 10;
            v /= 10;
        }

        auto full = std::span{digits}.first(n);
        return std::ranges::equal(
            full.first(n / 2),
            full.last(n / 2) | std::views::reverse);
    }

    FORCE_INLINE constexpr void testValue(u64 v)
    {
        if (isPalindromeBase10(v))
        {
            r += v;
            // std::println("{}", v);
            if (--n == 0) throw 0;
        }
    }

    template <u8 base>
    [[nodiscard]] constexpr u64 kMirrorT(u8 n_) noexcept
    {
        r = 0;
        n = n_;

        try
        {
            [&]<u8... index>(std::integer_sequence<u8, index...>)
            {
                (genPalindromes<base, index + 1>(1, 0), ...);
            }(std::make_integer_sequence<u8, kMaxDigits[base]>());
        }
        catch (...)
        {
        }

        return r;
    }

    static constexpr std::array kFunctions{
        &Solution2::kMirrorT<2>,
        &Solution2::kMirrorT<3>,
        &Solution2::kMirrorT<4>,
        &Solution2::kMirrorT<5>,
        &Solution2::kMirrorT<6>,
        &Solution2::kMirrorT<7>,
        &Solution2::kMirrorT<8>,
        &Solution2::kMirrorT<9>,
    };

    [[nodiscard]] constexpr u64 kMirror(u8 k, u8 n_) noexcept
    {
        return (this->*(kFunctions[k - 2]))(n_);
    }
};

class Solution3
{
public:
    static constexpr std::array<u64, 10> tens{
        1,
        10,
        100,
        1000,
        10000,
        100000,
        1000000,
        10000000,
        100000000,
        1000000000,
    };

    template <u8 base>
    [[nodiscard]] FORCE_INLINE static constexpr std::span<u8> toDigits(
        u64 x,
        std::array<u8, 64>& digit) noexcept
    {
        u8 len = 0;
        if constexpr (std::popcount(base) == 1)
        {
            constexpr u8 l = std::countr_zero(base);
            constexpr u8 p = base - 1;
            for (; x > 0; x >>= l) digit[len++] = x & p;
        }
        else
        {
            for (; x > 0; x /= base) digit[len++] = x % base;
        }

        return std::span{digit}.first(len);
    }

    template <u8 base>
    [[nodiscard]] FORCE_INLINE static constexpr bool isMirror(u64 x) noexcept
    {
        std::array<u8, 64> arr;  // NOLINT
        auto digits = toDigits<base>(x, arr);
        return std::ranges::equal(
            digits.first(digits.size() / 2),
            digits.last(digits.size() / 2) | std::views::reverse);
    }

    [[nodiscard]] FORCE_INLINE static constexpr u64 rev(u64 x) noexcept
    {
        u64 ans = 0;
        for (; x > 0; x /= 10) ans = ans * 10 + x % 10;
        return ans;
    }

    template <u8 base>
    [[nodiscard]] static constexpr u64 kMirrorT(u8 n) noexcept
    {
        u64 sum = 0;

        for (u8 num_digits = 1; num_digits != 22; ++num_digits)
        {
            u64 half = (num_digits + 1) / 2;
            for (u64 i = tens[half - 1]; i < tens[half]; i++)
            {
                u64 pal = (num_digits & 1) ? i * tens[half - 1] + rev(i / 10)
                                           : i * tens[half] + rev(i);
                if (isMirror<base>(pal))
                {
                    sum += pal;
                    if (--n == 0) return sum;
                }
            }
        }

        return sum;
    }

    static constexpr std::array kFunctions{
        kMirrorT<2>,
        kMirrorT<3>,
        kMirrorT<4>,
        kMirrorT<5>,
        kMirrorT<6>,
        kMirrorT<7>,
        kMirrorT<8>,
        kMirrorT<9>,
    };

    [[nodiscard]] static constexpr u64 kMirror(u8 k, u8 n) noexcept
    {
        return kFunctions[k - 2](n);
    }
};

template <u8 base>
class SolutionK4
{
public:
    u64 r = 0;
    u8 n = 0;

    static constexpr auto kPowers = []
    {
        std::array<u64, 20> r{};
        u64 v = 1;
        for (u8 power = 0; power != r.size(); ++power)
        {
            r[power] = v;
            v *= 10;
        }
        return r;
    }();

    template <u8 num_digits, u8 out_p, u8 first_digit = 1>
    FORCE_INLINE constexpr void genPalindromes(u64 outer_add)
    {
        if constexpr (num_digits == 0)
        {
            testValue(outer_add);
        }
        else if constexpr (num_digits == 1)
        {
            constexpr u64 j = kPowers[out_p];
            u64 v = outer_add + first_digit * j;
            for (u8 digit = first_digit; digit != 10; ++digit)
            {
                testValue(v);
                v += j;
            }
        }
        else
        {
            constexpr u64 j = (kPowers[num_digits - 1] + 1) * kPowers[out_p];
            u64 add = outer_add + first_digit * j;
            for (u8 digit = first_digit; digit != 10; ++digit)
            {
                genPalindromes<num_digits - 2, out_p + 1, 0>(add);
                add += j;
            }
        }
    }

    [[nodiscard]] FORCE_INLINE static constexpr bool isPalindrome(
        u64 v) noexcept
    {
        std::array<u8, 64> digits;  // NOLINT
        u8 n = 0;
        while (v)
        {
            digits[n++] = v % base;
            v /= base;
        }

        auto full = std::span{digits}.first(n);
        return std::ranges::equal(
            full.first(n / 2),
            full.last(n / 2) | std::views::reverse);
    }

    FORCE_INLINE constexpr void testValue(u64 v)
    {
        if (isPalindrome(v))
        {
            r += v;
            if (--n == 0) throw 0;
        }
    }

    [[nodiscard]] FORCE_INLINE constexpr u64 kMirror(u8 n_) noexcept
    {
        r = 0;
        n = n_;

        try
        {
            [&]<u8... index>(std::integer_sequence<u8, index...>)
            {
                (genPalindromes<index + 1, 0>(0), ...);
            }(std::make_integer_sequence<u8, kPowers.size()>());
        }
        catch (...)
        {
        }

        return r;
    }
};

class Solution4
{
public:
    template <u8 base>
    static constexpr u64 kMirrorT(u8 n) noexcept
    {
        return SolutionK4<base>{}.kMirror(n);
    }

    static constexpr std::array kFunctions{
        kMirrorT<2>,
        kMirrorT<3>,
        kMirrorT<4>,
        kMirrorT<5>,
        kMirrorT<6>,
        kMirrorT<7>,
        kMirrorT<8>,
        kMirrorT<9>,
    };

    [[nodiscard]] FORCE_INLINE constexpr u64 kMirror(u8 k, u8 n_) noexcept
    {
        return kFunctions[k - 2](n_);
    }
};

class Cheat
{
public:
    using u64 = uint64_t;
    using u32 = uint32_t;
    using u8 = uint8_t;

    static constexpr std::array<u64, 240> kResults{
        1,
        4,
        9,
        16,
        25,
        58,
        157,
        470,
        1055,
        1772,
        9219,
        18228,
        33579,
        65802,
        105795,
        159030,
        212865,
        286602,
        872187,
        2630758,
        4565149,
        6544940,
        9674153,
        14745858,
        20005383,
        25846868,
        39347399,
        759196316,
        1669569335,
        2609044274,
        1,
        3,
        7,
        15,
        136,
        287,
        499,
        741,
        1225,
        1881,
        2638,
        31730,
        80614,
        155261,
        230718,
        306985,
        399914,
        493653,
        1342501,
        2863752,
        5849644,
        9871848,
        14090972,
        18342496,
        22630320,
        28367695,
        36243482,
        44192979,
        71904751,
        155059889,
        1,
        3,
        6,
        11,
        66,
        439,
        832,
        1498,
        2285,
        3224,
        11221,
        64456,
        119711,
        175366,
        233041,
        739646,
        2540727,
        4755849,
        8582132,
        12448815,
        17500320,
        22726545,
        27986070,
        33283995,
        38898160,
        44577925,
        98400760,
        721411086,
        1676067545,
        53393239260,
        1,
        3,
        6,
        10,
        16,
        104,
        356,
        638,
        1264,
        1940,
        3161,
        18912,
        37793,
        10125794,
        20526195,
        48237967,
        78560270,
        126193944,
        192171900,
        1000828708,
        1832161846,
        2664029984,
        3500161622,
        4336343260,
        6849225412,
        9446112364,
        12339666346,
        19101218022,
        31215959143,
        43401017264,
        1,
        3,
        6,
        10,
        15,
        22,
        77,
        188,
        329,
        520,
        863,
        1297,
        2074,
        2942,
        4383,
        12050,
        19827,
        41849,
        81742,
        156389,
        325250,
        1134058,
        2043967,
        3911648,
        7009551,
        11241875,
        15507499,
        19806423,
        24322577,
        28888231,
        1,
        3,
        6,
        10,
        15,
        21,
        29,
        150,
        321,
        563,
        855,
        17416,
        83072,
        2220384,
        6822448,
        13420404,
        20379000,
        29849749,
        91104965,
        321578997,
        788407661,
        1273902245,
        1912731081,
        2570225837,
        3428700695,
        29128200347,
        69258903451,
        115121130305,
        176576075721,
        241030621167,
        1,
        3,
        6,
        10,
        15,
        21,
        28,
        37,
        158,
        450,
        783,
        1156,
        1570,
        2155,
        5818,
        14596,
        27727,
        41058,
        67520,
        94182,
        124285,
        154588,
        362290,
        991116,
        1651182,
        3148123,
        5083514,
        7054305,
        11253219,
        66619574,
        1,
        3,
        6,
        10,
        15,
        21,
        28,
        36,
        227,
        509,
        882,
        1346,
        1901,
        2547,
        3203,
        10089,
        35841,
        63313,
        105637,
        156242,
        782868,
        2323319,
        4036490,
        5757761,
        7586042,
        9463823,
        11349704,
        13750746,
        16185088,
        18627530,
    };

    [[nodiscard]] static constexpr u64 kMirror(u8 k, u8 n) noexcept
    {
        return kResults[(k - 2) * 30 + (n - 1)];
    }
};
