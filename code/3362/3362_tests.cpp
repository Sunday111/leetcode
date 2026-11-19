#include "3362.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::maxRemoval;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[2,0,2] [[0,2],[0,2],[1,1]] 1

[1,2,3,4] [[0,3]] -1

[0,3] [[0,0],[0,0],[0,1],[0,1],[0,1]] 2
)cases");

using t3362 = SolutionTests<Solution>;

TEST_P(t3362, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.maxRemoval(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3362,
    t3362::parameters(kCases.size()),
    t3362::name);
