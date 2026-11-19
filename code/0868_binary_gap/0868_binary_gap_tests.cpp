#include "0868_binary_gap.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::binaryGap;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
22 2

8 0

5 2
)cases");

using t0868_binary_gap = SolutionTests<Solution>;

TEST_P(t0868_binary_gap, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.binaryGap(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0868_binary_gap,
    t0868_binary_gap::parameters(kCases.size()),
    t0868_binary_gap::name);
