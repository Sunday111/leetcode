#include <print>

#include "0166.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::fractionToDecimal;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
4 333 "0.(012)"

1 2 "0.5"
)cases");

using t0166 = SolutionTests<Solution>;

TEST_P(t0166, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.fractionToDecimal(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0166,
    t0166::parameters(kCases.size()),
    t0166::name);
