#include "1347.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest = &Solution::minSteps;

inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"bab"
"aba"
1

"leetcode"
"practice"
5

"anagram"
"mangaar"
0
)");

using t1347 = SolutionTests<Solution>;

TEST_P(t1347, MinOperations)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.minSteps(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1347,
    t1347::parameters(kCases.size()),
    t1347::name);
