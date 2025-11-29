#pragma once

#include <concepts>

#include "cast.hpp"
#include "force_inline.hpp"
#include "hot_path.hpp"
#include "integral_aliases.hpp"

inline constexpr u32 kMOD = 1'000'000'007;

struct ModInt
{
    FORCE_INLINE constexpr ModInt& operator+=(
        const ModInt& rhs) noexcept HOT_PATH
    {
        value += rhs.value;
        if (value >= kMOD) value -= kMOD;
        return *this;
    }

    [[nodiscard]] FORCE_INLINE constexpr ModInt operator+(
        const ModInt& rhs) const noexcept
    {
        auto copy = *this;
        copy += rhs;
        return copy;
    }

    FORCE_INLINE constexpr ModInt& operator-=(
        const ModInt& rhs) noexcept HOT_PATH
    {
        value -= rhs.value;
        return *this;
    }

    [[nodiscard]] FORCE_INLINE constexpr ModInt operator-(
        const ModInt& rhs) const noexcept HOT_PATH
    {
        auto copy = *this;
        copy -= rhs;
        return copy;
    }

    FORCE_INLINE constexpr ModInt& operator*=(
        const ModInt& rhs) noexcept HOT_PATH
    {
        u64 v = rhs.value;
        v *= value;
        if (v >= kMOD) v %= kMOD;
        value = cast<u32>(v);
        return *this;
    }

    [[nodiscard]] FORCE_INLINE constexpr ModInt operator*(
        const ModInt& rhs) const noexcept HOT_PATH
    {
        auto copy = *this;
        copy *= rhs;
        return copy;
    }

    [[nodiscard]] FORCE_INLINE constexpr ModInt inverse()
        const noexcept HOT_PATH
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

    FORCE_INLINE constexpr ModInt& operator/=(
        const ModInt& rhs) noexcept HOT_PATH
    {
        return *this *= rhs.inverse();
    }

    [[nodiscard]] FORCE_INLINE constexpr ModInt operator/(
        const ModInt& rhs) const noexcept HOT_PATH
    {
        auto copy = *this;
        copy /= rhs;
        return copy;
    }

    template <std::unsigned_integral Exp>
    [[nodiscard]] FORCE_INLINE constexpr ModInt pow(
        Exp exp) const noexcept HOT_PATH
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
