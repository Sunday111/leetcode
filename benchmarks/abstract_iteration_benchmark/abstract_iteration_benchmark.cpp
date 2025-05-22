#include <gtest/gtest.h>

#include <print>
#include <random>
#include <ranges>

#include "benchmark/benchmark.h"

class ValueProvider
{
public:
    static constexpr unsigned kSeed = 132412412;
    static constexpr int kBreakValue = -1;
    static constexpr size_t kNumVals = 1'000'000'000;
    static constexpr int kMOD = 1'000'000'007;
    std::vector<std::optional<int>> data;

    static const ValueProvider& Get()
    {
        static ValueProvider p{};
        return p;
    }

    [[nodiscard]] int RegularLoop() const
    {
        int sum = 0;
        for (auto opt : data)
        {
            if (opt)
            {
                if (*opt == kBreakValue) break;
                sum += *opt;
                sum %= kMOD;
            }
        }

        return sum;
    }

    enum class ControlFlow : uint8_t
    {
        kContinue,
        kBreak,
    };

    template <typename Callback>
    void ForEachValue(Callback callback) const
    {
        for (auto opt : data)
        {
            if (opt && callback(*opt) == ControlFlow::kBreak) break;
        }
    }

    [[nodiscard]] int CallbackLoop() const
    {
        int sum = 0;
        ForEachValue(
            [&](int value)
            {
                if (value == kBreakValue) return ControlFlow::kBreak;
                sum += value;
                sum %= kMOD;
                return ControlFlow::kContinue;
            });

        return sum;
    }

    [[nodiscard]] auto GetValues() const
    {
        return data |
               std::views::filter([](const auto& opt)
                                  { return opt.has_value(); }) |
               std::views::transform([](const auto& opt) { return *opt; });
    }

    int RangesLoop() const
    {
        int sum = 0;
        for (const auto& value : GetValues())
        {
            if (value == kBreakValue) break;
            sum += value;
            sum %= kMOD;
        }
        return sum;
    }

    template <typename Callback>
    void ForEachValueExceptions(Callback callback) const
    {
        try
        {
            for (auto opt : data)
            {
                if (opt) callback(*opt);
            }
        }
        catch (const ControlFlow cf)
        {
            assert(cf == ControlFlow::kBreak);
        }
    }

    [[nodiscard]] int CallbackLoopExceptions() const
    {
        int sum = 0;
        ForEachValueExceptions(
            [&](int value)
            {
                if (value == kBreakValue) throw ControlFlow::kBreak;  // NOLINT
                sum += value;
                sum %= kMOD;
            });

        return sum;
    }

private:
    ValueProvider()
    {
        std::mt19937 rnd(kSeed);
        std::uniform_int_distribution<int> val_distr{
            0,
            std::numeric_limits<int>::max()};

        data.reserve(kNumVals + 1);
        for (size_t i = 0; i != kNumVals / 2; ++i)
        {
            std::optional<int> v;
            if ((rnd() % 2) == 0) v = val_distr(rnd);
            data.push_back(v);
        }

        data.push_back(kBreakValue);

        for (size_t i = 0; i != kNumVals / 2; ++i)
        {
            std::optional<int> v;
            if ((rnd() % 2) == 0) v = val_distr(rnd);
            data.push_back(v);
        }
    }
};

static void BM_RegularLoop(benchmark::State& state)
{
    const auto& value_provider = ValueProvider::Get();

    for (auto _ : state)
    {
        auto s = value_provider.RegularLoop();
        benchmark::DoNotOptimize(s);
    }
}

static void BM_CallbackLoop(benchmark::State& state)
{
    const auto& value_provider = ValueProvider::Get();

    for (auto _ : state)
    {
        auto s = value_provider.CallbackLoop();
        benchmark::DoNotOptimize(s);
    }
}

static void BM_CallbackLoopExceptions(benchmark::State& state)
{
    const auto& value_provider = ValueProvider::Get();

    for (auto _ : state)
    {
        auto s = value_provider.CallbackLoopExceptions();
        benchmark::DoNotOptimize(s);
    }
}

static void BM_RangesLoop(benchmark::State& state)
{
    const auto& value_provider = ValueProvider::Get();

    for (auto _ : state)
    {
        auto s = value_provider.RangesLoop();
        benchmark::DoNotOptimize(s);
    }
}

TEST(AbstractIterationResult, Test1)
{
    const auto& value_provider = ValueProvider::Get();
    auto regular_loop_sum = value_provider.RegularLoop();
    std::println("Regular loop sum: {}", regular_loop_sum);
    auto callback_loop_sum = value_provider.CallbackLoop();
    std::println("Callback loop sum: {}", callback_loop_sum);
    auto ranges_loop_sum = value_provider.RangesLoop();
    std::println("Ranges loop sum: {}", ranges_loop_sum);
    auto callback_loop_exceptions_sum = value_provider.RangesLoop();
    std::println(
        "Callback loop (exceptions) sum: {}",
        callback_loop_exceptions_sum);
    EXPECT_EQ(regular_loop_sum, callback_loop_sum);
    EXPECT_EQ(regular_loop_sum, ranges_loop_sum);
    EXPECT_EQ(regular_loop_sum, callback_loop_exceptions_sum);
}

BENCHMARK(BM_RegularLoop);             // NOLINT
BENCHMARK(BM_CallbackLoop);            // NOLINT
BENCHMARK(BM_RangesLoop);              // NOLINT
BENCHMARK(BM_CallbackLoopExceptions);  // NOLINT
BENCHMARK_MAIN();                      // NOLINT
