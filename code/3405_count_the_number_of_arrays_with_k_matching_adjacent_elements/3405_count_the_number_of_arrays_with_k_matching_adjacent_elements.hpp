#pragma once

#include <array>
#include <bitset>

#ifdef __GNUC__
#define ATTR inline __attribute__((always_inline))
#else
#define ATTR inline
#endif

using u8 = uint8_t;
using u32 = uint32_t;
using u64 = uint64_t;
static constexpr int kMOD = 1'000'000'007;

struct ModInt
{
    ATTR constexpr ModInt& operator+=(const ModInt& rhs) noexcept
    {
        value += rhs.value;
        if (value >= kMOD) value -= kMOD;
        return *this;
    }

    [[nodiscard]] ATTR constexpr ModInt operator+(const ModInt& rhs) noexcept
    {
        auto copy = *this;
        copy += rhs;
        return copy;
    }

    ATTR constexpr ModInt& operator*=(const ModInt& rhs) noexcept
    {
        u64 v = rhs.value;
        v *= value;
        if (v >= kMOD) v %= kMOD;
        value = static_cast<u32>(v);
        return *this;
    }

    [[nodiscard]] ATTR constexpr ModInt operator*(
        const ModInt& rhs) const noexcept
    {
        auto copy = *this;
        copy *= rhs;
        return copy;
    }

    [[nodiscard]] ATTR constexpr ModInt inverse() const noexcept
    {
        auto a = value;
        u32 x0 = 1, x1 = 0, mod = kMOD;
        while (a)
        {
            u32 q = mod / a;
            u32 r = mod % a;
            u32 x2 = x1 - q * x0;
            mod = a;
            a = r;
            x1 = x0;
            x0 = x2;
        }
        return {(x1 + kMOD) % kMOD};
    }

    ATTR constexpr ModInt& operator/=(const ModInt& rhs) noexcept
    {
        return *this *= rhs.inverse();
    }

    [[nodiscard]] ATTR constexpr ModInt operator/(
        const ModInt& rhs) const noexcept
    {
        auto copy = *this;
        copy /= rhs;
        return copy;
    }

    [[nodiscard]] ATTR constexpr ModInt pow(u32 exp) const noexcept
    {
        if (exp == 0) return {1};
        std::bitset<32> bits(exp);
        ModInt ans = *this;
        u8 i = (31 - std::countl_zero(exp)) & 0xFF;
        while (i)
        {
            --i;
            ans *= ans;
            ans *= bits[i] ? *this : ModInt{1};
        }
        return ans;
    }

    u32 value = 0;
};

class Solution
{
public:
    static constexpr auto kFactorials = []
    {
        std::array<ModInt, 100000> fact;  // NOLINT
        u64 product = 1;
        fact[0].value = 1;
        for (u32 i = 1; i != 100000; ++i)
        {
            product *= i;
            if (product >= kMOD) product %= kMOD;
            fact[i].value = static_cast<u32>(product);
        }

        return fact;
    }();

    [[nodiscard]] ATTR static constexpr ModInt combinationsCount(
        u32 n,
        u32 k) noexcept
    {
        auto r = kFactorials[n];
        r /= kFactorials[k];
        r /= kFactorials[n - k];
        return r;
    }

    [[nodiscard]] ATTR static constexpr u32
    countGoodArrays(u32 n, u32 m, u32 k) noexcept
    {
        return (ModInt{m} * ModInt{m - 1}.pow(n - k - 1) *
                combinationsCount(n - 1, k))
            .value;
    }
};
