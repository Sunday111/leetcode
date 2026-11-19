#include "0827.hpp"
#include "parse_2d_array.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::largestIsland;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[[1,0],[0,1]] 3

[[1,1],[1,1]] 4
)cases");

using t0827 = SolutionTests<Solution>;

TEST_P(t0827, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.largestIsland(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0827,
    t0827::parameters(kCases.size()),
    t0827::name);
