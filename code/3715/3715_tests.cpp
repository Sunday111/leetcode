#include "3715.hpp"
#include "parse_2d_array.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::sumOfAncestors;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
3 [[0,1],[1,2]] [2,8,2] 3

3 [[0,1],[0,2]] [1,2,4] 1

4 [[0,1],[0,2],[1,3]] [1,2,9,4] 2
)cases");

using t3715 = SolutionTests<Solution>;

TEST_P(t3715, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.sumOfAncestors(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3715,
    t3715::parameters(kCases.size()),
    t3715::name);
