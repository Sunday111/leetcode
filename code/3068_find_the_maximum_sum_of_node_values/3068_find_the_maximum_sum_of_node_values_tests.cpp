#include "3068_find_the_maximum_sum_of_node_values.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::maximumValueSum;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[67,13,79,13,75,11,0,41,94] 7 [[0,1],[3,7],[4,7],[6,5],[6,0],[0,2],[7,2],[7,8]] 407
)cases");

using t3068_find_the_maximum_sum_of_node_values = SolutionTests<Solution>;

TEST_P(t3068_find_the_maximum_sum_of_node_values, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.maximumValueSum(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3068_find_the_maximum_sum_of_node_values,
    t3068_find_the_maximum_sum_of_node_values::parameters(kCases.size()),
    t3068_find_the_maximum_sum_of_node_values::name);
