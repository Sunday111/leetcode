#include "2749.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::makeTheIntegerZero;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
3 -2 3
)cases");

using t2749 = SolutionTests<Solution>;

TEST_P(t2749, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.makeTheIntegerZero(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2749,
    t2749::parameters(kCases.size()),
    t2749::name);
