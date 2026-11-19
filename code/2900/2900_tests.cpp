#include "2900.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::getLongestSubsequence;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
["d","g"] [0,1] ["d","g"]
)cases");

using t2900 = SolutionTests<Solution>;

TEST_P(t2900, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.getLongestSubsequence(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2900,
    t2900::parameters(kCases.size()),
    t2900::name);
