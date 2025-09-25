#include "0029_divide_two_integers.hpp"
#include "0029_divide_two_integers_msb.hpp"
#include "benchmark/benchmark.h"
#include "random_data.hpp"

template <typename S>
static void BenchmarkTemplate(benchmark::State& state) noexcept
{
    auto& data = RandomData::Instance();
    for (auto _ : state)
    {
        int64_t sum = 0;
        for (auto [a, b] : data.values)
        {
            sum += S::divide(a, b);
        }
        benchmark::DoNotOptimize(sum);
    }
}

static void BM_DivideMSB(benchmark::State& state)
{
    BenchmarkTemplate<SolutionMSB>(state);
}

static void BM_Divide(benchmark::State& state)
{
    BenchmarkTemplate<Solution>(state);
}

BENCHMARK(BM_DivideMSB);  // NOLINT
BENCHMARK(BM_Divide);     // NOLINT
BENCHMARK_MAIN();         // NOLINT
