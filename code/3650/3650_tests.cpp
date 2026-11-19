#include "3650.hpp"
#include "parse_2d_array.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::minCost;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
4 [[0,1,3],[3,1,1],[2,3,4],[0,2,2]] 5

4 [[0,2,1],[2,1,1],[1,3,1],[2,3,3]] 3

4 [[2,3,25],[2,1,18],[3,1,2]] -1
)cases");

using t3650 = SolutionTests<Solution>;

TEST_P(t3650, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.minCost(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3650,
    t3650::parameters(kCases.size()),
    t3650::name);
