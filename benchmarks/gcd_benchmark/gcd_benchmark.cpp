#include <concepts>
#include <numeric>

#include "benchmark/benchmark.h"

// Iterative Euclidean Algorithm
template <std::integral T>
constexpr T gcd(T a, T b)
{
    while (b != 0)
    {
        T temp = b;
        b = a % b;
        a = temp;
    }

    if constexpr (std::is_unsigned_v<T>)
    {
        return a;
    }
    else
    {
        // Handle negative inputs
        return (a >= 0) ? a : -a;
    }
}

// Binary GCD (Stein’s Algorithm)
template <std::unsigned_integral T>
constexpr T binary_gcd(T u, T v)
{
    if (u == 0) return v;
    if (v == 0) return u;

    // Count common factors of 2
    int shift = 0;
    while (((u | v) & 1) == 0)
    {
        u >>= 1;
        v >>= 1;
        ++shift;
    }

    // Remove all factors of 2 from u
    while ((u & 1) == 0) u >>= 1;

    do
    {
        // Remove all factors of 2 from v
        while ((v & 1) == 0) v >>= 1;

        // Ensure u <= v
        if (u > v) std::swap(u, v);

        v -= u;
    } while (v != 0);

    return u << shift;
}

template <typename gcd_fn>
static uint32_t benchmark_loop(gcd_fn fn)
{
    uint32_t r = 0;

    constexpr uint32_t kMod = 1'000'007;

    for (uint32_t i = 1; i != 10'000; ++i)
    {
        for (uint32_t j = 50'000; j != 51'000; ++j)
        {
            r = (r + fn(i, j)) % kMod;
        }
    }

    return r;
}

static void BM_STL(benchmark::State& state)
{
    for (auto _ : state)
    {
        auto r = benchmark_loop([](auto a, auto b) { return std::gcd(a, b); });
        benchmark::DoNotOptimize(r);
    }
}

static void BM_IterativeEuclidean(benchmark::State& state)
{
    for (auto _ : state)
    {
        auto r = benchmark_loop([](auto a, auto b) { return ::gcd(a, b); });
        benchmark::DoNotOptimize(r);
    }
}

static void BM_BinaryGCD(benchmark::State& state)
{
    for (auto _ : state)
    {
        auto r =
            benchmark_loop([](auto a, auto b) { return binary_gcd(a, b); });
        benchmark::DoNotOptimize(r);
    }
}

BENCHMARK(BM_STL);                 // NOLINT
BENCHMARK(BM_IterativeEuclidean);  // NOLINT
BENCHMARK(BM_BinaryGCD);           // NOLINT
BENCHMARK_MAIN();                  // NOLINT
