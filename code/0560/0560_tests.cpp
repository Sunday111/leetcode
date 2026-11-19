#include "0560.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::subarraySum;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[1,1,1] 2 2

[1,2,3] 3 2
)cases");

using t0560 = SolutionTests<Solution>;

TEST_P(t0560, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.subarraySum(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0560,
    t0560::parameters(kCases.size()),
    t0560::name);
