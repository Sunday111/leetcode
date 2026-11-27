#include <algorithm>
#include <array>
#include <concepts>
#include <iterator>
#include <vector>

#include "gtest/gtest.h"
#include "math/for_each_prime_factor.hpp"
#include "math/linear_sieve.hpp"
#include "math/precompute_primes.hpp"

static_assert(std::same_as<decltype(precompute_primes<0>()), RawArray<u8, 0>>);
static_assert(std::same_as<decltype(precompute_primes<1>()), RawArray<u8, 0>>);
static_assert(std::ranges::equal(precompute_primes<2>().data, std::array{2}));
static_assert(std::ranges::equal(
    precompute_primes<13>().data,
    std::array{2, 3, 5, 7, 11, 13}));
static_assert(std::ranges::equal(
    precompute_primes<16>().data,
    precompute_primes<13>().data));

static_assert(
    []
    {
        u16 spf[257]{};
        u16 primes[60]{};
        return linear_sieve<256>(spf, primes, 60) == 54 && spf[256] == 2 &&
               primes[53] == 251;
    }());

TEST(PrimeFactorization, ReinitializesCallerStorageAndFactorsEveryValue)
{
    std::array<u16, 301> spf{};
    std::array<u32, 100> primes{};
    spf.fill(42);
    const u32 count =
        linear_sieve<300>(spf.data(), primes.data(), primes.size());
    constexpr auto list = precompute_primes<300, u32>();
    EXPECT_EQ(count, 62u);
    EXPECT_EQ(std::size(list.data), count);
    EXPECT_TRUE(
        std::equal(std::begin(list.data), std::end(list.data), primes.begin()));
    for (u32 x = 1; x <= 300; ++x)
    {
        u32 rest = x;
        std::vector<std::pair<u32, u32>> expected, actual;
        for (u32 p = 2; p <= rest; ++p)
        {
            u32 power = 0;
            while (rest % p == 0)
            {
                rest /= p;
                ++power;
            }
            if (power) expected.emplace_back(p, power);
        }
        auto collect = [&](u32 p, u32 power)
        {
            actual.emplace_back(p, power);
        };
        for_each_prime_factor(spf.data(), x, collect);
        ASSERT_EQ(actual, expected);
    }
}
