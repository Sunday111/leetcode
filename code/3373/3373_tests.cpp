#include "3373.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::maxTargetNodes;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[[0,1],[0,2],[2,3],[2,4]] [[0,1],[0,2],[0,3],[2,7],[1,4],[4,5],[4,6]] [8,7,7,8,8]

[[2,0],[4,1],[2,3],[2,4]] [[0,1],[0,2],[0,3]] [6,5,5,6,6]
)cases");

using t3373 = SolutionTests<Solution>;

TEST_P(t3373, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.maxTargetNodes(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3373,
    t3373::parameters(kCases.size()),
    t3373::name);
