#include "3727_minimum_alternating_sum_of_squares.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::maxAlternatingSum;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[1,2,3] 12

[1,-1,2,-2,3,-3] 16
)cases");

using t3727_minimum_alternating_sum_of_squares = SolutionTests<Solution>;

TEST_P(t3727_minimum_alternating_sum_of_squares, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.maxAlternatingSum(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3727_minimum_alternating_sum_of_squares,
    t3727_minimum_alternating_sum_of_squares::parameters(kCases.size()),
    t3727_minimum_alternating_sum_of_squares::name);
