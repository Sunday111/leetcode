#include "2411_smallest_subarrays_with_maximum_bitwise_or.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::smallestSubarrays;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[0] [1]

[1,0,2,1,3] [3,3,2,2,1]
)cases");

using t2411_smallest_subarrays_with_maximum_bitwise_or =
    SolutionTests<Solution>;

TEST_P(t2411_smallest_subarrays_with_maximum_bitwise_or, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.smallestSubarrays(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2411_smallest_subarrays_with_maximum_bitwise_or,
    t2411_smallest_subarrays_with_maximum_bitwise_or::parameters(kCases.size()),
    t2411_smallest_subarrays_with_maximum_bitwise_or::name);
