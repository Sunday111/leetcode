#include <algorithm>
#include <random>
#include <string>
#include <utility>
#include <vector>

#include "benchmark/benchmark.h"
#include "radix_sort/radix_sort.hpp"

namespace
{
enum class Input : u8
{
    Random,
    FewKeys,
    Sorted
};

template <u8 bits>
[[gnu::noinline, gnu::no_sanitize_address]] void sort_values(u32* values, u32 n)
{
    radix_sort<bits == 10 ? 30 : 32, bits>(values, n);
}

template <u8 bits>
void benchmark_sort(benchmark::State& state, Input input)
{
    const auto n = static_cast<u32>(state.range(0));
    std::mt19937 random{1234};
    std::vector<u32> source(n);
    for (u32& value : source)
    {
        value = static_cast<u32>(random());
        if (input == Input::FewKeys) value = (value % 16) * 0x11111111u;
        if constexpr (bits == 10) value &= 0x3FFFFFFFu;
    }
    if (input == Input::Sorted) std::ranges::sort(source);

    std::vector<u32> work(n);
    for (auto _ : state)
    {
        state.PauseTiming();
        std::ranges::copy(source, work.begin());
        state.ResumeTiming();
        sort_values<bits>(work.data(), n);
        benchmark::ClobberMemory();
    }
}

template <u8 bits>
void register_cases(const char* name)
{
    for (auto [input, label] :
         {std::pair{Input::Random, "random"},
          std::pair{Input::FewKeys, "16_keys"},
          std::pair{Input::Sorted, "sorted"}})
    {
        benchmark::internal::Benchmark* bench = benchmark::RegisterBenchmark(
            (std::string{name} + "/" + label).c_str(),
            benchmark_sort<bits>,
            input);
        if constexpr (bits == 10)
        {
            for (int n : {1025, 2048, 8192, 32768, 65536, 100001})
            {
                bench->Arg(n);
            }
        }
        else
        {
            bench->Arg(128)->Arg(8192)->Arg(100001);
        }
    }
}
}  // namespace

int main(int argc, char** argv)
{
    register_cases<8>("radix/8bit");
    register_cases<4>("radix/4bit");
    register_cases<10>("radix/10bit");
    benchmark::Initialize(&argc, argv);
    if (benchmark::ReportUnrecognizedArguments(argc, argv)) return 1;
    benchmark::RunSpecifiedBenchmarks();
    benchmark::Shutdown();
}
