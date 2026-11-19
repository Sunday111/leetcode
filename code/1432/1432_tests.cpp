#include "1432.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::maxDiff;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
111 888
)cases");

using t1432_max_difference_you_can_get_from_changing_an_integer =
    SolutionTests<Solution>;

TEST_P(t1432_max_difference_you_can_get_from_changing_an_integer, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.maxDiff(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1432_max_difference_you_can_get_from_changing_an_integer,
    t1432_max_difference_you_can_get_from_changing_an_integer::parameters(
        kCases.size()),
    t1432_max_difference_you_can_get_from_changing_an_integer::name);
