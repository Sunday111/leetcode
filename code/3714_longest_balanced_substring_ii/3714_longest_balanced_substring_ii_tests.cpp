#include <string>
#include <string_view>

#include "3714_longest_balanced_substring_ii.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::longestBalanced;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"abbac" 4

"aabcc" 3

"aba" 2

"bacbbc" 4
)cases");

using t3714_longest_balanced_substring_ii = SolutionTests<Solution>;

TEST_P(t3714_longest_balanced_substring_ii, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.longestBalanced(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3714_longest_balanced_substring_ii,
    t3714_longest_balanced_substring_ii::parameters(kCases.size()),
    t3714_longest_balanced_substring_ii::name);
