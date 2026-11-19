#include "1143.hpp"
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

using t1143 = SolutionTests<Solution>;

TEST_P(t1143, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.longestCommonSubsequence(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1143,
    t1143::parameters(kCases.size()),
    t1143::name);
