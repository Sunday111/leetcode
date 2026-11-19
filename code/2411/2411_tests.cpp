#include "2411.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::smallestSubarrays;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[0] [1]

[1,0,2,1,3] [3,3,2,2,1]
)cases");

using t2411 = SolutionTests<Solution>;

TEST_P(t2411, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.smallestSubarrays(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2411,
    t2411::parameters(kCases.size()),
    t2411::name);
