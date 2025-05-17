#include <random>

#include "3337_total_characters_in_string_after_transformations_2.hpp"
#include "3337_total_characters_in_string_after_transformations_2_s2.hpp"
#include "benchmark/benchmark.h"

struct Params
{
    static constexpr unsigned kSeed = 12345;
    static constexpr uint32_t t = 1'000'000'000;
    static constexpr size_t string_len = 10'000;

    static const Params& Get()
    {
        static auto val = [&]()
        {
            Params p;

            std::mt19937 rnd{kSeed};
            std::uniform_int_distribution distr{0, 25};

            p.s.reserve(string_len);
            for (size_t i = 0; i != string_len; ++i)
            {
                p.s.push_back(static_cast<char>('a' + distr(rnd)));
            }

            p.nums.resize(26);
            for (auto& v : p.nums) v = distr(rnd);

            return p;
        }();

        return val;
    }

    std::string s;
    std::vector<int> nums;
};

template <typename F>
void benchmark_loop(F f, const Params& p)
{
    auto r = f(p.s, p.t, p.nums);
    benchmark::DoNotOptimize(r);
}

static void BM_Solution1(benchmark::State& state)
{
    const auto& params = Params::Get();
    for (auto _ : state)
    {
        benchmark_loop(Solution::lengthAfterTransformations, params);
    }
}

static void BM_Solution2(benchmark::State& state)
{
    const auto& params = Params::Get();
    for (auto _ : state)
    {
        benchmark_loop(Solution2::lengthAfterTransformations, params);
    }
}

BENCHMARK(BM_Solution1);  // NOLINT
BENCHMARK(BM_Solution2);  // NOLINT
BENCHMARK_MAIN();         // NOLINT
