#include "0827_Making_A_Large_Island.hpp"
#include "parse_2d_array.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::largestIsland;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[[1,0],[0,1]] 3

[[1,1],[1,1]] 4
)cases");

using t0827_Making_A_Large_Island = SolutionTests<Solution>;

TEST_P(t0827_Making_A_Large_Island, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.largestIsland(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0827_Making_A_Large_Island,
    t0827_Making_A_Large_Island::parameters(kCases.size()),
    t0827_Making_A_Large_Island::name);
