#include "0494.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::findTargetSumWays;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[1,1,1,1,1] 3 5
)cases");

using t0494 = SolutionTests<Solution>;

TEST_P(t0494, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.findTargetSumWays(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0494,
    t0494::parameters(kCases.size()),
    t0494::name);
