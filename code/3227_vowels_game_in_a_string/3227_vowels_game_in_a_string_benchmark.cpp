#include <benchmark/benchmark.h>

#include <random>

static constexpr auto is_vowel_bitset = []
{
    uint64_t bs = 0;
    for (char c : std::string_view{"aeiou"})
    {
        bs |= (uint64_t{1} << (c - 64));
    }
    return bs;
}();

constexpr bool is_vowel_a(char c) noexcept
{
    return is_vowel_bitset & (uint64_t{1} << (c - 64));
}

constexpr bool is_vowel_b(char c) noexcept
{
    return (0x104111 >> (c - 'a')) & 1;
}

// Generate test data
static std::vector<char> make_test_data(std::size_t size)
{
    std::mt19937 rng(42);
    std::uniform_int_distribution<int> dist('a', 'z');
    std::vector<char> data(size);
    for (auto& c : data) c = static_cast<char>(dist(rng));
    return data;
}

constexpr size_t kStringSize = 1'000'000'000;

// Benchmarks
static void BM_IsVowelA(benchmark::State& state)
{
    auto data = make_test_data(kStringSize);
    std::size_t count = 0;
    for (auto _ : state)
    {
        for (auto c : data) count += is_vowel_a(c);
    }
    benchmark::DoNotOptimize(count);
}

static void BM_IsVowelB(benchmark::State& state)
{
    auto data = make_test_data(kStringSize);
    std::size_t count = 0;
    for (auto _ : state)
    {
        for (auto c : data) count += is_vowel_b(c);
    }
    benchmark::DoNotOptimize(count);
}

// Register benchmarks
BENCHMARK(BM_IsVowelA);  // NOLINT
BENCHMARK(BM_IsVowelB);  // NOLINT
BENCHMARK_MAIN();        // NOLINT
