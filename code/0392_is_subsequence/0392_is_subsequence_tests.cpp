#include "0392_is_subsequence.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::isSubsequence;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"aaaaaa" "bbaaaa" false

"abc" "ahbgdc" true

"axc" "ahbgdc" false
)cases");

using t0392_is_subsequence = SolutionTests<Solution>;

TEST_P(t0392_is_subsequence, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.isSubsequence(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0392_is_subsequence,
    t0392_is_subsequence::parameters(kCases.size()),
    t0392_is_subsequence::name);
