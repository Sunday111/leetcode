#pragma once

#include <cassert>
#include <concepts>
#include <limits>

#include "cast/cast.hpp"
#include "integral_aliases.hpp"

// spf holds limit + 1 entries. primes holds at least the number of primes
// through limit.
template <
    u32 limit,
    std::unsigned_integral Factor,
    std::unsigned_integral Prime>
constexpr u32
linear_sieve(Factor* spf, Prime* primes, [[maybe_unused]] u32 capacity) noexcept
{
    static_assert(limit <= std::numeric_limits<Factor>::max());
    static_assert(limit <= std::numeric_limits<Prime>::max());
    for (u64 x = 0; x <= limit; ++x) spf[x] = 0;
    u32 count = 0;
    for (u64 x = 2; x <= limit; ++x)
    {
        if (!spf[x])
        {
            assert(count < capacity);
            spf[x] = cast<Factor>(x);
            primes[count++] = cast<Prime>(x);
        }
        for (u32 i = 0; i != count; ++i)
        {
            const u32 prime = primes[i];
            const u64 multiple = x * prime;
            if (multiple > limit) break;
            spf[multiple] = static_cast<Factor>(prime);
            if (prime == spf[x]) break;
        }
    }
    return count;
}
