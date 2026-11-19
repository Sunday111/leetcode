#include "3170.hpp"
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

using t3170 = SolutionTests<Solution>;

TEST_P(t3170, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.clearStars(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3170,
    t3170::parameters(kCases.size()),
    t3170::name);
