#pragma once

#include <concepts>
#include <limits>

#include "raw_array.hpp"
#include "uint_for_value.hpp"

template <u32 limit, std::unsigned_integral Prime = UintForValue<limit>>
    requires(limit <= std::numeric_limits<Prime>::max())
[[nodiscard]] consteval auto precompute_primes() noexcept
{
    if constexpr (limit < 2)
    {
        return RawArray<Prime, 0>{};
    }
    else
    {
        constexpr auto composite = []
        {
            RawArray<bool, limit / 2 + limit % 2> flags{};
            flags.data[0] = true;  // 1 is not prime.
            for (u64 p = 3; p * p <= limit; p += 2)
            {
                if (flags.data[p / 2]) continue;
                for (u64 m = p * p; m <= limit; m += 2 * p)
                {
                    flags.data[m / 2] = true;
                }
            }
            return flags;
        }();

        constexpr auto count = [](const auto& flags)
        {
            u32 n = 1;  // Include 2.
            for (bool marked : flags.data) n += !marked;
            return n;
        }(composite);

        RawArray<Prime, count> primes{};
        primes.data[0] = 2;
        u32 written = 1;
        for (u64 p = 3; p <= limit; p += 2)
        {
            if (!composite.data[p / 2])
            {
                primes.data[written++] = static_cast<Prime>(p);
            }
        }
        return primes;
    }
}
