#include "3719_longest_balanced_subarray_i.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::longestBalanced;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[2,5,4,3] 4

[3,2,2,5,4] 5

[1,2,3,2] 3
)cases");

using t3719_longest_balanced_subarray_i = SolutionTests<Solution>;

TEST_P(t3719_longest_balanced_subarray_i, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.longestBalanced(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3719_longest_balanced_subarray_i,
    t3719_longest_balanced_subarray_i::parameters(kCases.size()),
    t3719_longest_balanced_subarray_i::name);
