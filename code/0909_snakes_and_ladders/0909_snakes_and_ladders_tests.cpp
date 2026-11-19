#include "0909_snakes_and_ladders.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::snakesAndLadders;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[[-1,-1,-1,-1,-1,-1],[-1,-1,-1,-1,-1,-1],[-1,-1,-1,-1,-1,-1],[-1,35,-1,-1,13,-1],[-1,-1,-1,-1,-1,-1],[-1,15,-1,-1,-1,-1]]
4

[[-1,-1,-1],[-1,9,8],[-1,8,9]] 1
)cases");

using t0909_snakes_and_ladders = SolutionTests<Solution>;

TEST_P(t0909_snakes_and_ladders, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.snakesAndLadders(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0909_snakes_and_ladders,
    t0909_snakes_and_ladders::parameters(kCases.size()),
    t0909_snakes_and_ladders::name);
