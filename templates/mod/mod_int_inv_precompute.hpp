#pragma once

#include <array>
#include <cassert>
#include <cstddef>

#include "mod/mod_int_inv.hpp"

template <std::size_t size>
inline constexpr auto mod_int_inv_precompute(
    const std::array<ModInt, size>& divisors)
{
    std::array<ModInt, size> inverses;
    for (std::size_t i = 0; i != size; ++i)
    {
        assert(divisors[i].value != 0);
        inverses[i] = inverse(divisors[i]);
    }
    return inverses;
}
