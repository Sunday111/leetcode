#include "3068.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::maximumValueSum;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[67,13,79,13,75,11,0,41,94] 7 [[0,1],[3,7],[4,7],[6,5],[6,0],[0,2],[7,2],[7,8]] 407
)cases");

using t3068 = SolutionTests<Solution>;

TEST_P(t3068, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.maximumValueSum(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3068,
    t3068::parameters(kCases.size()),
    t3068::name);
