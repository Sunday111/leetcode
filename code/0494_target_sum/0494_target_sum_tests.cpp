#include "0494_target_sum.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::findTargetSumWays;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[1,1,1,1,1] 3 5
)cases");

using t0494_target_sum = SolutionTests<Solution>;

TEST_P(t0494_target_sum, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.findTargetSumWays(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0494_target_sum,
    t0494_target_sum::parameters(kCases.size()),
    t0494_target_sum::name);
