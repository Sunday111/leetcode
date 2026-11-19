#include "0204_count_primes.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::countPrimes;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
10 4

0 0

1 0

5000000 348513
)cases");

using t0204_count_primes = SolutionTests<Solution>;

TEST_P(t0204_count_primes, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.countPrimes(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0204_count_primes,
    t0204_count_primes::parameters(kCases.size()),
    t0204_count_primes::name);
