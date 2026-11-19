#include "1590.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::minSubarray;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[3,1,4,2] 6 1
)cases");

using t1590 = SolutionTests<Solution>;

TEST_P(t1590, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.minSubarray(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1590,
    t1590::parameters(kCases.size()),
    t1590::name);
