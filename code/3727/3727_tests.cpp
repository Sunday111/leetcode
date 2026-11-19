#include "3727.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::maxAlternatingSum;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[1,2,3] 12

[1,-1,2,-2,3,-3] 16
)cases");

using t3727 = SolutionTests<Solution>;

TEST_P(t3727, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.maxAlternatingSum(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3727,
    t3727::parameters(kCases.size()),
    t3727::name);
