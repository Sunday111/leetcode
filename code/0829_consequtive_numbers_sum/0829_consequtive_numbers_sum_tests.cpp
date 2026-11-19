#include "0829_consequtive_numbers_sum.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::consecutiveNumbersSum;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
5 2

9 3

15 4

999999 64

99999999 48
)cases");

using t0829_consequtive_numbers_sum = SolutionTests<Solution>;

TEST_P(t0829_consequtive_numbers_sum, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.consecutiveNumbersSum(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0829_consequtive_numbers_sum,
    t0829_consequtive_numbers_sum::parameters(kCases.size()),
    t0829_consequtive_numbers_sum::name);
