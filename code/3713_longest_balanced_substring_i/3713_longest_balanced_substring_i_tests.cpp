#include "3713_longest_balanced_substring_i.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::longestBalanced;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"abbac" 4

"nlllk" 3
)cases");

using t3713_longest_balanced_substring_i = SolutionTests<Solution>;

TEST_P(t3713_longest_balanced_substring_i, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.longestBalanced(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3713_longest_balanced_substring_i,
    t3713_longest_balanced_substring_i::parameters(kCases.size()),
    t3713_longest_balanced_substring_i::name);
