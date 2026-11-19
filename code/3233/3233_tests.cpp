#include "3233.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::nonSpecialCount;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
5 7 3

4 16 11

1 100000 99935

1 4 3
)cases");

using t3233 = SolutionTests<Solution>;

TEST_P(t3233, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.nonSpecialCount(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3233,
    t3233::parameters(kCases.size()),
    t3233::name);
