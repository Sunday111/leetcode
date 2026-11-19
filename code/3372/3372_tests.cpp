#include "3372.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::maxTargetNodes;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[[0,1],[0,2],[2,3],[2,4]] [[0,1],[0,2],[0,3],[2,7],[1,4],[4,5],[4,6]] 2 [9,7,9,8,8]
)cases");

using t3372 = SolutionTests<Solution>;

TEST_P(t3372, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.maxTargetNodes(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3372,
    t3372::parameters(kCases.size()),
    t3372::name);
