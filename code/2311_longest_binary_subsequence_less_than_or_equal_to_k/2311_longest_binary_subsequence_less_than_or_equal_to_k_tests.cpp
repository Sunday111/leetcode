#include "2311_longest_binary_subsequence_less_than_or_equal_to_k.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::longestSubsequence;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"1001010" 5 5
)cases");

using t2311_longest_binary_subsequence_less_than_or_equal_to_k =
    SolutionTests<Solution>;

TEST_P(t2311_longest_binary_subsequence_less_than_or_equal_to_k, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.longestSubsequence(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2311_longest_binary_subsequence_less_than_or_equal_to_k,
    t2311_longest_binary_subsequence_less_than_or_equal_to_k::parameters(
        kCases.size()),
    t2311_longest_binary_subsequence_less_than_or_equal_to_k::name);
