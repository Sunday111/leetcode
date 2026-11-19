#include "3818.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::minimumPrefixLength;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[1,-1,2,3,3,4,5] 4

[4,3,-2,-5] 3

[1,2,3,4] 0
)cases");

using t3818_minimum_prefix_removal_to_make_array_strictly_increasing =
    SolutionTests<Solution>;

TEST_P(t3818_minimum_prefix_removal_to_make_array_strictly_increasing, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.minimumPrefixLength(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3818_minimum_prefix_removal_to_make_array_strictly_increasing,
    t3818_minimum_prefix_removal_to_make_array_strictly_increasing::parameters(
        kCases.size()),
    t3818_minimum_prefix_removal_to_make_array_strictly_increasing::name);
