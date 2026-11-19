#include <immintrin.h>

#include <print>

#include "0762.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::countPrimeSetBits;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
6 10 4

10 15 5

990000 1000000 3754
)cases");

using t0762 = SolutionTests<Solution>;

TEST_P(t0762, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.countPrimeSetBits(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0762,
    t0762::parameters(kCases.size()),
    t0762::name);
