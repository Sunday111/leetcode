#include "0829.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::consecutiveNumbersSum;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
5 2

9 3

15 4

999999 64

99999999 48
)cases");

using t0829 = SolutionTests<Solution>;

TEST_P(t0829, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.consecutiveNumbersSum(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0829,
    t0829::parameters(kCases.size()),
    t0829::name);
