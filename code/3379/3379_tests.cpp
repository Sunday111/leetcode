#include "3379.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::constructTransformedArray;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[3,-2,1,1] [1,1,1,3]
)cases");

using t3379 = SolutionTests<Solution>;

TEST_P(t3379, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.constructTransformedArray(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3379,
    t3379::parameters(kCases.size()),
    t3379::name);
