#include "3202_find_the_maximum_length_of_valid_subsequence_2.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::maximumLength;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[1,2,3,4,5] 2 5

[1,9,3,10,10] 4 2
)cases");

using t3202_find_the_maximum_length_of_valid_subsequence_2 =
    SolutionTests<Solution>;

TEST_P(t3202_find_the_maximum_length_of_valid_subsequence_2, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.maximumLength(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3202_find_the_maximum_length_of_valid_subsequence_2,
    t3202_find_the_maximum_length_of_valid_subsequence_2::parameters(
        kCases.size()),
    t3202_find_the_maximum_length_of_valid_subsequence_2::name);
