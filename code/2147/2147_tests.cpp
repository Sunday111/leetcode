#include "2147.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::numberOfWays;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"SSPPSPS" 3

"PPSPSP" 1

"S" 0

"P" 0
)cases");

using t2147 = SolutionTests<Solution>;

TEST_P(t2147, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.numberOfWays(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2147,
    t2147::parameters(kCases.size()),
    t2147::name);
