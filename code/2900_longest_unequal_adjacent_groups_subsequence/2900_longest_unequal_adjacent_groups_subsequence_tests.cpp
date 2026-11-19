#include "2900_longest_unequal_adjacent_groups_subsequence.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::getLongestSubsequence;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
["d","g"] [0,1] ["d","g"]
)cases");

using t2900_longest_unequal_adjacent_groups_subsequence =
    SolutionTests<Solution>;

TEST_P(t2900_longest_unequal_adjacent_groups_subsequence, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.getLongestSubsequence(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2900_longest_unequal_adjacent_groups_subsequence,
    t2900_longest_unequal_adjacent_groups_subsequence::parameters(
        kCases.size()),
    t2900_longest_unequal_adjacent_groups_subsequence::name);
