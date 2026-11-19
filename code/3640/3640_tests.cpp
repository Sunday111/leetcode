#include "3640.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::maxSumTrionic;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[0,-2,-1,-3,0,2,-1] -4

[1,4,2,7] 14
)cases");

using t3640 = SolutionTests<Solution>;

TEST_P(t3640, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.maxSumTrionic(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3640,
    t3640::parameters(kCases.size()),
    t3640::name);
