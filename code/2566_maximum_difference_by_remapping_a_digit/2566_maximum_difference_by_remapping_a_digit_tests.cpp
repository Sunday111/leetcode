#include "2566_maximum_difference_by_remapping_a_digit.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::minMaxDifference;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
1001 9009
)cases");

using t2566_maximum_difference_by_remapping_a_digit = SolutionTests<Solution>;

TEST_P(t2566_maximum_difference_by_remapping_a_digit, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.minMaxDifference(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2566_maximum_difference_by_remapping_a_digit,
    t2566_maximum_difference_by_remapping_a_digit::parameters(kCases.size()),
    t2566_maximum_difference_by_remapping_a_digit::name);
