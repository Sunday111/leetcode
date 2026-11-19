#include "0070_climbing_stairs.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::climbStairs;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
1 1

2 2

3 3

45 1836311903
)cases");

using t0070_climbing_stairs = SolutionTests<Solution>;

TEST_P(t0070_climbing_stairs, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.climbStairs(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0070_climbing_stairs,
    t0070_climbing_stairs::parameters(kCases.size()),
    t0070_climbing_stairs::name);
