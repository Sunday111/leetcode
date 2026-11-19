#include <print>

#include "0166_fraction_to_recurring_decimal.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::fractionToDecimal;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
4 333 "0.(012)"

1 2 "0.5"
)cases");

using t0166_fraction_to_recurring_decimal = SolutionTests<Solution>;

TEST_P(t0166_fraction_to_recurring_decimal, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.fractionToDecimal(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0166_fraction_to_recurring_decimal,
    t0166_fraction_to_recurring_decimal::parameters(kCases.size()),
    t0166_fraction_to_recurring_decimal::name);
