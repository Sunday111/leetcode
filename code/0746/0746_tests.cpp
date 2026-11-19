#include "0746.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::minCostClimbingStairs;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[10,15,20] 15

[1,100,1,1,1,100,1,1,100,1] 6
)cases");

using t0746 = SolutionTests<Solution>;

TEST_P(t0746, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.minCostClimbingStairs(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0746,
    t0746::parameters(kCases.size()),
    t0746::name);
