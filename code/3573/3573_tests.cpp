#include "3573.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::maximumProfit;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[1,7,9,8,2] 2 14

[12,16,19,19,8,1,19,13,9] 3 36
)cases");

using t3573 = SolutionTests<Solution>;

TEST_P(t3573, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.maximumProfit(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3573,
    t3573::parameters(kCases.size()),
    t3573::name);
