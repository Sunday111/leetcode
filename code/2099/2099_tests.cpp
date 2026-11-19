#include "2099.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::maxSubsequence;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[50,-75] 2 [50,-75]
)cases");

using t2099 = SolutionTests<Solution>;

TEST_P(t2099, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.maxSubsequence(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2099,
    t2099::parameters(kCases.size()),
    t2099::name);
