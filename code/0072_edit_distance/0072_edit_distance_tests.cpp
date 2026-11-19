#include "0072_edit_distance.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::minDistance;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"horse" "ros" 3

"intention" "execution" 5

"" "" 0

"abc" "defghi" 6

"leet" "code" 4

"azertyqsdfghqwerty" "azertyjklmqwerty" 6

"aaaaaaaaaaaaaaaaaaaaaa" "aaaaaaaaaaaaaav" 8

"aaayuio" "hjklaaa" 7

"sea" "eat" 2
)cases");

using t0072_edit_distance = SolutionTests<Solution>;

TEST_P(t0072_edit_distance, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.minDistance(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0072_edit_distance,
    t0072_edit_distance::parameters(kCases.size()),
    t0072_edit_distance::name);
