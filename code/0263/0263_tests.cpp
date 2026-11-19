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

using t0263_ugly_number = SolutionTests<Solution>;

TEST_P(t0263_ugly_number, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args) { return solution.isUgly(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0263_ugly_number,
    t0263_ugly_number::parameters(kCases.size()),
    t0263_ugly_number::name);
