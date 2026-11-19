#include <algorithm>
#include <ranges>
#include <tuple>
#include <unordered_map>

#include "3629.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::minJumps;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,2,4,6]
2

[2,3,4,7,9]
2

[4,6,5,8]
3
)");

/*inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
[1,2,4,6]
2

[2,3,4,7,9]
2

[4,6,5,8]
3


)");*/

using t3629 = SolutionTests<Solution>;

TEST_P(t3629, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.minJumps(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3629,
    t3629::parameters(kCases.size()),
    t3629::name);

/*

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
