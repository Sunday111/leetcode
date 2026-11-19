#include "3170_lexicographically_minimum_string_after_removing_stars.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::clearStars;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"aaba*" "aab"

"abc" "abc"

"b*n" "n"

"abc*de*fgh*" "defgh"

"a*b*c*d*" ""

"abcde*f*" "cdef"

"d*yed" "yed"
)cases");

using t3170_lexicographically_minimum_string_after_removing_stars =
    SolutionTests<Solution>;

TEST_P(t3170_lexicographically_minimum_string_after_removing_stars, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.clearStars(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3170_lexicographically_minimum_string_after_removing_stars,
    t3170_lexicographically_minimum_string_after_removing_stars::parameters(
        kCases.size()),
    t3170_lexicographically_minimum_string_after_removing_stars::name);
