#include "1143_longest_common_subsequence.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::longestCommonSubsequence;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"abcde" "ace" 3

"abc" "abc" 3

"abc" "def" 0

"a" "ttta" 1

"wggi" "g" 1

"iitt" "tttttttttt" 2

"jijiijjpji" "jjji" 4
)cases");

using t1143_longest_common_subsequence = SolutionTests<Solution>;

TEST_P(t1143_longest_common_subsequence, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.longestCommonSubsequence(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1143_longest_common_subsequence,
    t1143_longest_common_subsequence::parameters(kCases.size()),
    t1143_longest_common_subsequence::name);
