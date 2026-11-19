#include "2099_find_subsequence_of_length_k_with_largest_sum.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::maxSubsequence;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[50,-75] 2 [50,-75]
)cases");

using t2099_find_subsequence_of_length_k_with_largest_sum =
    SolutionTests<Solution>;

TEST_P(t2099_find_subsequence_of_length_k_with_largest_sum, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.maxSubsequence(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2099_find_subsequence_of_length_k_with_largest_sum,
    t2099_find_subsequence_of_length_k_with_largest_sum::parameters(
        kCases.size()),
    t2099_find_subsequence_of_length_k_with_largest_sum::name);
