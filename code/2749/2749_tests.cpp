#include "2749.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::makeTheIntegerZero;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
3 -2 3
)cases");

using t2749_minimum_operations_to_make_the_integer_zero =
    SolutionTests<Solution>;

TEST_P(t2749_minimum_operations_to_make_the_integer_zero, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.makeTheIntegerZero(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2749_minimum_operations_to_make_the_integer_zero,
    t2749_minimum_operations_to_make_the_integer_zero::parameters(
        kCases.size()),
    t2749_minimum_operations_to_make_the_integer_zero::name);
