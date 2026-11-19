#include "0264.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::nthUglyNumber;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
10 12

1690 2123366400
)cases");

using t0264_nth_ugly_number = SolutionTests<Solution>;

TEST_P(t0264_nth_ugly_number, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.nthUglyNumber(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0264_nth_ugly_number,
    t0264_nth_ugly_number::parameters(kCases.size()),
    t0264_nth_ugly_number::name);
