#include "0264.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::nthUglyNumber;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
10 12

1690 2123366400
)cases");

using t0264 = SolutionTests<Solution>;

TEST_P(t0264, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.nthUglyNumber(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0264,
    t0264::parameters(kCases.size()),
    t0264::name);
