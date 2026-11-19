#include "2311.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::longestSubsequence;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"1001010" 5 5
)cases");

using t2311 = SolutionTests<Solution>;

TEST_P(t2311, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.longestSubsequence(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2311,
    t2311::parameters(kCases.size()),
    t2311::name);
