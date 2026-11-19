#include "0868.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::binaryGap;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
22 2

8 0

5 2
)cases");

using t0868 = SolutionTests<Solution>;

TEST_P(t0868, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.binaryGap(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0868,
    t0868::parameters(kCases.size()),
    t0868::name);
