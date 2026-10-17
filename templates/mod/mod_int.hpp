#pragma once

#include <concepts>

#include "integral_aliases.hpp"

inline constexpr u32 kMOD = 1'000'000'007;

struct ModInt
{
    [[gnu::always_inline]] constexpr ModInt& operator+=(
        const ModInt& rhs) noexcept;

    [[nodiscard, gnu::always_inline]] constexpr ModInt operator+(
        const ModInt& rhs) const noexcept;

    [[gnu::always_inline]] constexpr ModInt& operator-=(
        const ModInt& rhs) noexcept;

    [[nodiscard, gnu::always_inline]] constexpr ModInt operator-(
        const ModInt& rhs) const noexcept;

    [[gnu::always_inline]] constexpr ModInt& operator*=(
        const ModInt& rhs) noexcept;

    [[nodiscard, gnu::always_inline]] constexpr ModInt operator*(
        const ModInt& rhs) const noexcept;

    [[nodiscard, gnu::always_inline]] constexpr ModInt inverse() const noexcept;

    [[gnu::always_inline]] constexpr ModInt& operator/=(
        const ModInt& rhs) noexcept;

    [[nodiscard, gnu::always_inline]] constexpr ModInt operator/(
        const ModInt& rhs) const noexcept;

    template <std::unsigned_integral Exp>
    [[nodiscard, gnu::always_inline]] constexpr ModInt pow(
        Exp exp) const noexcept;

    u32 value = 0;
};
