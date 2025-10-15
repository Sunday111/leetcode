#include "1768_merge_strings_alternately_simple.hpp"
#include "1768_merge_strings_alternately_sse2.hpp"
#include "benchmark/benchmark.h"
#include "strings_for_testing.hpp"

template <typename target_fn>
static uint32_t benchmark_loop(target_fn fn)
{
    uint32_t r = 0;
    auto& strings = StringsForTesting::Get().strings;
    for (u32 i = 0; i != strings.size(); ++i)
    {
        auto& a = strings[i];
        for (u32 j = i + 1; j != strings.size(); ++j)
        {
            auto& b = strings[j];
            auto s = fn(a, b);
            r += static_cast<uint8_t>(s[3]);
        }
    }

    return r;
}

static void BM_SSE2(benchmark::State& state)
{
    [[maybe_unused]] auto& strings = StringsForTesting::Get().strings;
    for (auto _ : state)
    {
        auto r = benchmark_loop(
            [](auto& a, auto& b)
            { return solution_sse2::Solution{}.mergeAlternately(a, b); });
        benchmark::DoNotOptimize(r);
    }
}

static void BM_Simple(benchmark::State& state)
{
    [[maybe_unused]] auto& strings = StringsForTesting::Get().strings;
    for (auto _ : state)
    {
        auto r = benchmark_loop(
            [](auto& a, auto& b)
            { return simple::Solution{}.mergeAlternately(a, b); });
        benchmark::DoNotOptimize(r);
    }
}

BENCHMARK(BM_Simple);  // NOLINT
BENCHMARK(BM_SSE2);    // NOLINT
BENCHMARK_MAIN();      // NOLINT
