#pragma once

#include <array>

#include "force_inline.hpp"
#include "integral_aliases.hpp"

template <u32 n>
class Factorizer
{
public:
    std::array<u32, n + 1> spf{};
    std::array<u32, 10'000> primes;
    u32 num_primes = 0;

    Factorizer() noexcept  // NOLINT
    {
        for (u32 x = 2u; x <= n; ++x)
        {
            if (spf[x] == 0u)
            {
                spf[x] = x;
                primes[num_primes++] = x;
            }

            for (u32 prime_index = 0; prime_index != num_primes; ++prime_index)
            {
                u32 prime = primes[prime_index];
                const u64 prod64 = u64{prime} * u64{x};
                if (prod64 > n) break;
                u32 prod = static_cast<u32>(prod64);
                spf[prod] = prime;
                if (prime == spf[x]) break;
            }
        }
    }

    template <typename Callback>
    FORCE_INLINE void factorize(u32 x, Callback callback) const noexcept
    {
        while (x > 1)
        {
            u32 prime = spf[x], power = 0u;
            while (!(x % prime))
            {
                x /= prime;
                ++power;
            }
            callback(prime, power);
        }
    }
};
