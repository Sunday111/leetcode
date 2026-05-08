#include <tuple>

#include "3629_test_cases.hpp"
#include "gtest/gtest.h"

class t3629 : public ::testing::TestWithParam<size_t>
{
public:
};

TEST_P(t3629, Test)
{
    auto [inputs, expected] = kCases[GetParam()];
    Solution instance{};
    auto f = std::bind_front(kMethodToTest, &instance);
    auto actual = std::apply(f, inputs);
    ASSERT_EQ(expected, actual);
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3629,
    ::testing::Range(size_t{0}, kCases.size()),
    [](const testing::TestParamInfo<size_t>& info)
    { return "C" + std::to_string(info.index); });

/*
#include <algorithm>
#include <ranges>
#include <unordered_map>

TEST(t3629x, meow)
{
std::unordered_map<u32, u32> x_freq, n_freq;
for (u32 i = 1; i != 1'000'001; ++i)
{
    std::array<std::pair<u32, u32>, 15> f;
    u32 num_primes = 0;
    u32 x = 1;
    factorizer.factorize(
        i,
        [&](u32 prime, u32 power)
        {
            assert(num_primes != f.size());
            f[num_primes++] = {prime, power};
            x *= power + 1;
        });
    x_freq[x]++;
    n_freq[num_primes]++;
}

auto kv = [](const auto& x)
{
    return std::pair{x.first, x.second};
};
auto xx = std::ranges::to<std::vector>(x_freq | std::views::transform(kv));
std::ranges::sort(xx);
auto nn = std::ranges::to<std::vector>(n_freq | std::views::transform(kv));
std::ranges::sort(nn);

std::println("x freq:");
for (auto [k, v] : xx) std::println("    {}: {}", k, v);

std::println("n freq:");
for (auto [k, v] : nn) std::println("    {}: {}", k, v);
ASSERT_TRUE(false);
}*/
