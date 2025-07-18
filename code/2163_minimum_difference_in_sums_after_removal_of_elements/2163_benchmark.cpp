#include <random>

#include "2163_minimum_difference_in_sums_after_removal_of_elements.hpp"
#include "benchmark/benchmark.h"

struct Params
{
    static constexpr unsigned kSeed = 12345;

    static const Params& Get()
    {
        static auto val = [&]()
        {
            Params p;

            std::mt19937 rnd{kSeed};
            std::uniform_int_distribution distr{0, 25};

            constexpr size_t num_inputs = 10000;
            p.inputs.resize(num_inputs);
            for (auto& nums : p.inputs)
            {
                nums.resize(100'000);
                for (auto& v : nums) v = rnd() % 100'001;
            }

            return p;
        }();

        return val;
    }

    std::vector<std::vector<u32>> inputs;
};

template <typename Solution>
void benchmark_loop(const Params& p)
{
    for (auto& nums : p.inputs)
    {
        auto r = Solution::minimumDifference(nums);
        benchmark::DoNotOptimize(r);
    }
}

static void BM_AllBranches(benchmark::State& state)
{
    const auto& params = Params::Get();
    for (auto _ : state)
    {
        benchmark_loop<all_branches::Solution>(params);
    }
}

static void BM_OneBranch(benchmark::State& state)
{
    const auto& params = Params::Get();
    for (auto _ : state)
    {
        benchmark_loop<one_branch::Solution>(params);
    }
}

static void BM_TwoBranches(benchmark::State& state)
{
    const auto& params = Params::Get();
    for (auto _ : state)
    {
        benchmark_loop<two_branches::Solution>(params);
    }
}

static void BM_Branchless(benchmark::State& state)
{
    const auto& params = Params::Get();
    for (auto _ : state)
    {
        benchmark_loop<branchless::Solution>(params);
    }
}

BENCHMARK(BM_AllBranches)->Unit(benchmark::kMillisecond);  // NOLINT
BENCHMARK(BM_TwoBranches)->Unit(benchmark::kMillisecond);  // NOLINT
BENCHMARK(BM_OneBranch)->Unit(benchmark::kMillisecond);    // NOLINT
BENCHMARK(BM_Branchless)->Unit(benchmark::kMillisecond);   // NOLINT
BENCHMARK_MAIN();                                          // NOLINT
