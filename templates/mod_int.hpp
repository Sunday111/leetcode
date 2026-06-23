#pragma once

#include <concepts>

#include "cast.hpp"
#include "integral_aliases.hpp"

inline constexpr u32 kMOD = 1'000'000'007;

struct ModInt
{
    [[gnu::always_inline]] constexpr ModInt& operator+=(
        const ModInt& rhs) noexcept
    {
        value += rhs.value;
        value -= kMOD & -u32{value >= kMOD};
        return *this;
    }

    [[nodiscard, gnu::always_inline]] constexpr ModInt operator+(
        const ModInt& rhs) const noexcept
    {
        auto copy = *this;
        copy += rhs;
        return copy;
    }

    [[gnu::always_inline]] constexpr ModInt& operator-=(
        const ModInt& rhs) noexcept
    {
        value += kMOD & -u32{value < rhs.value};
        value -= rhs.value;
        return *this;
    }

    [[nodiscard, gnu::always_inline]] constexpr ModInt operator-(
        const ModInt& rhs) const noexcept
    {
        auto copy = *this;
        copy -= rhs;
        return copy;
    }

    [[gnu::always_inline]] constexpr ModInt& operator*=(
        const ModInt& rhs) noexcept
    {
        u64 v = rhs.value;
        v *= value;
        if (v >= kMOD) v %= kMOD;
        value = cast<u32>(v);
        return *this;
    }

    [[nodiscard, gnu::always_inline]] constexpr ModInt operator*(
        const ModInt& rhs) const noexcept
    {
        auto copy = *this;
        copy *= rhs;
        return copy;
    }

    [[nodiscard, gnu::always_inline]] constexpr ModInt inverse() const noexcept
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

    [[gnu::always_inline]] constexpr ModInt& operator/=(
        const ModInt& rhs) noexcept
    {
        return *this *= rhs.inverse();
    }

    [[nodiscard, gnu::always_inline]] constexpr ModInt operator/(
        const ModInt& rhs) const noexcept
    {
        auto copy = *this;
        copy /= rhs;
        return copy;
    }

    template <std::unsigned_integral Exp>
    [[nodiscard, gnu::always_inline]] constexpr ModInt pow(
        Exp exp) const noexcept
    {
        ModInt r{1}, b = *this;

        while (exp)
        {
            // these two lines are equal to if (exp & 1) r *= b;
            u32 t = -(exp & 1);
            r *= ModInt((b.value & t) + (1u & ~t));

            b *= b;
            exp >>= 1;
        }

        return r;
    }

    u32 value = 0;
};
