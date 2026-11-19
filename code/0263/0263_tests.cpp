#include "0263.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::isUgly;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
0 false

1 true

6 true

14 false
)cases");

using t0263 = SolutionTests<Solution>;

TEST_P(t0263, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args) { return solution.isUgly(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0263,
    t0263::parameters(kCases.size()),
    t0263::name);
