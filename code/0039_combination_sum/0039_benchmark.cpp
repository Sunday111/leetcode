#include "0039_combination_sum.hpp"
#include "0039_combination_sum_2.hpp"
#include "0039_combination_sum_3.hpp"
#include "benchmark/benchmark.h"

static void BM_DirectSolution(benchmark::State& state)
{
    Solution solver;
    std::vector<int32_t> candidates = {2, 3, 5, 6, 7, 8, 9, 10, 11, 12};
    int32_t target = 40;

    for (auto _ : state)
    {
        auto result = solver.combinationSum(candidates, target);
        benchmark::DoNotOptimize(result);
    }
}

static void BM_RecursiveSolution(benchmark::State& state)
{
    Solution2 solver;
    std::vector<int> candidates = {2, 3, 5, 6, 7, 8, 9, 10, 11, 12};
    int target = 40;

    for (auto _ : state)
    {
        auto result = solver.combinationSum(candidates, target);
        benchmark::DoNotOptimize(result);
    }
}

static void BM_RecursiveBitsetsSolution(benchmark::State& state)
{
    Solution3 solver;
    std::vector<int> candidates = {2, 3, 5, 6, 7, 8, 9, 10, 11, 12};
    int target = 40;

    for (auto _ : state)
    {
        auto result = solver.combinationSum(candidates, target);
        benchmark::DoNotOptimize(result);
    }
}

BENCHMARK(BM_DirectSolution);            // NOLINT
BENCHMARK(BM_RecursiveSolution);         // NOLINT
BENCHMARK(BM_RecursiveBitsetsSolution);  // NOLINT
BENCHMARK_MAIN();                        // NOLINT
