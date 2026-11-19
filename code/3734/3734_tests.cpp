#include "3734.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

inline static constexpr auto kMethodToTest =
    &Solution::lexPalindromicPermutation;
inline static const auto kCases = parse_test_cases<kMethodToTest>(R"(
"baba"
"abba"
"baab"

"baba"
"bbaa"
""

"abc"
"abb"
""

"aac"
"abb"
"aca"

"a"
"z"
""
)");

using t3734 = SolutionTests<Solution>;

TEST_P(t3734, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.lexPalindromicPermutation(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3734,
    t3734::parameters(kCases.size()),
    t3734::name);
