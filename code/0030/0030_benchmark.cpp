#include <cassert>

#include "0030.hpp"
#include "benchmark/benchmark.h"
#include "cast.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::findSubstring;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"barfoothefoobarman"
["foo","bar"]
[0,9]

"wordgoodgoodgoodbestword"
["word","good","best","word"]
[]

"barfoofoobarthefoobarman"
["bar","foo","the"]
[6,9,12]

"a"
["aa"]
[]

"ab"
["ab"]
[0]

"foobar"
["foo","bar","baz"]
[]

"aaaaaa"
["aa","aa"]
[0,1,2]

"barfoofoofoobar"
["bar","foo","foo"]
[0,6]

"barfooxxxfoobar"
["bar","foo"]
[0,9]

"barfooxbarfoo"
["bar","foo"]
[0,7]

"wordgoodgoodgoodbestword"
["word","good","best","good"]
[8]

"aaaaaaaa"
["aa","bb"]
[]

"bbbfoobbb"
["foo"]
[3]

"abbacaabc"
["a","b","c"]
[2,6]

"abcabcabc"
["a","b","c"]
[0,1,2,3,4,5,6]

"abcxabcabc"
["a","b","c"]
[0,4,5,6,7]

"ababa"
["a"]
[0,2,4]

)");

static void BM_Examples(benchmark::State& state)
{
    const auto& [original, expected] = kCases[cast<size_t>(state.range(0))];
    for ([[maybe_unused]] auto _ : state)
    {
        auto [s, words] = original;
        Solution solver;
        auto result = solver.findSubstring(s, words);
        benchmark::DoNotOptimize(result);
    }
}

static void BM_RepeatedWords(benchmark::State& state)
{
    std::string s(10'000, 'a');
    std::vector<std::string> original(5000, "a");
    for ([[maybe_unused]] auto _ : state)
    {
        auto words = original;
        Solution solver;
        auto result = solver.findSubstring(s, words);
        benchmark::DoNotOptimize(result);
    }
}

static void BM_BrokenWindows(benchmark::State& state)
{
    const auto word_len = cast<size_t>(state.range(0));
    const std::string word(word_len, 'a');
    const std::vector<std::string> words(4, word);
    std::string s;
    while (s.size() + 9 * word_len <= 10'000)
    {
        s.append(8 * word_len, 'a');
        s.append(word_len, 'b');
    }
    for ([[maybe_unused]] auto _ : state)
    {
        auto input_words = words;
        Solution solver;
        auto result = solver.findSubstring(s, input_words);
        benchmark::DoNotOptimize(result);
    }
}

static void BM_DistinctWords(benchmark::State& state)
{
    const auto num_words = cast<size_t>(state.range(0));
    const auto word_len = cast<size_t>(state.range(1));
    assert(num_words > 0 && word_len > 0);
    std::vector<std::string> words;
    for (size_t i = 0; i < num_words; ++i)
    {
        std::string word(word_len, 'a');
        auto value = i;
        for (auto& c : word)
        {
            c = static_cast<char>('a' + value % 26);
            value /= 26;
        }
        words.push_back(word);
    }
    std::string s;
    while (s.size() + word_len <= 10'000)
    {
        s += words[(s.size() / word_len) % num_words];
    }
    for ([[maybe_unused]] auto _ : state)
    {
        auto input_words = words;
        Solution solver;
        auto result = solver.findSubstring(s, input_words);
        benchmark::DoNotOptimize(result);
    }
}

BENCHMARK(BM_Examples)
    ->DenseRange(0, cast<int64_t>(kCases.size()) - 1);  // NOLINT
BENCHMARK(BM_RepeatedWords);                            // NOLINT
BENCHMARK(BM_BrokenWindows)
    ->Arg(1)
    ->Arg(2)
    ->Arg(3)
    ->Arg(8)
    ->Arg(12)
    ->Arg(13)
    ->Arg(30);  // NOLINT
BENCHMARK(BM_DistinctWords)
    ->Args({16, 3})
    ->Args({256, 3})
    ->Args({256, 2})
    ->Args({256, 8})
    ->Args({256, 12})
    ->Args({256, 13})
    ->Args({256, 30});  // NOLINT
BENCHMARK_MAIN();       // NOLINT
