#pragma once

#include <concepts>

#include "integral_aliases.hpp"

template <std::unsigned_integral Factor, typename Callback>
[[gnu::always_inline]] constexpr void
for_each_prime_factor(const Factor* spf, u32 x, Callback&& callback) noexcept
{
    while (x > 1)
    {
        u32 prime = spf[x];
        u32 power = 0;
        while (!(x % prime))
        {
            x /= prime;
            ++power;
        }
        callback(prime, power);
    }
}
