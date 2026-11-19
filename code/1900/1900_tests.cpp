#include "1900.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::earliestAndLatest;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
11 2 4 [3,4]

5 1 5 [1,1]
)cases");

using t1900 = SolutionTests<Solution>;

TEST_P(t1900, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.earliestAndLatest(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1900,
    t1900::parameters(kCases.size()),
    t1900::name);
