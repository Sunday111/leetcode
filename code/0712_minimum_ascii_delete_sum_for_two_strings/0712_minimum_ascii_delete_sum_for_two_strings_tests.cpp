#include "0712_minimum_ascii_delete_sum_for_two_strings.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::minimumDeleteSum;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"sea" "eat" 231

"delete" "leet" 403
)cases");

using t0712_minimum_ascii_delete_sum_for_two_strings = SolutionTests<Solution>;

TEST_P(t0712_minimum_ascii_delete_sum_for_two_strings, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.minimumDeleteSum(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0712_minimum_ascii_delete_sum_for_two_strings,
    t0712_minimum_ascii_delete_sum_for_two_strings::parameters(kCases.size()),
    t0712_minimum_ascii_delete_sum_for_two_strings::name);
