#include "1137.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::tribonacci;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
4 4

25 1389537
)cases");

using t1137 = SolutionTests<Solution>;

TEST_P(t1137, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.tribonacci(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1137,
    t1137::parameters(kCases.size()),
    t1137::name);
