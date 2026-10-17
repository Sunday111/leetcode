#pragma once

#include <array>
#include <cassert>
#include <cstddef>

#include "integral_aliases.hpp"
#include "mod/mod_int_mul.hpp"

template <std::size_t lim_factorial>
constexpr ModInt binomial_coefficient(
    const std::array<ModInt, lim_factorial>& factorials,
    const std::array<ModInt, lim_factorial>& inverse_factorials,
    u32 n,
    u32 k) noexcept
{
    assert(n >= k);
    return factorials[n] * inverse_factorials[k] * inverse_factorials[n - k];
}
