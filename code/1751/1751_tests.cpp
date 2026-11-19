#include "1751.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::maxValue;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[[1,2,4],[3,4,3],[2,3,1]] 2 7

[[1,2,4],[3,4,3],[2,3,10]] 2 10

[[1,1,1],[2,2,2],[3,3,3],[4,4,4]] 3 9
)cases");

using t1751 = SolutionTests<Solution>;

TEST_P(t1751, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.maxValue(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1751,
    t1751::parameters(kCases.size()),
    t1751::name);
