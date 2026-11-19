#include "2901.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::getWordsInLongestSubsequence;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
["a","b","c","d"] [1,2,3,4] ["a","b","c","d"]

["bdb","aaa","ada"] [2,1,3] ["aaa","ada"]
)cases");

using t2901 = SolutionTests<Solution>;

TEST_P(t2901, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.getWordsInLongestSubsequence(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2901,
    t2901::parameters(kCases.size()),
    t2901::name);
