#include "0068.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::fullJustify;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
["This","is","an","example","of","text","justification."]
16
["This    is    an","example  of text","justification.  "]
)cases");

using t0068 = SolutionTests<Solution>;

TEST_P(t0068, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.fullJustify(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0068,
    t0068::parameters(kCases.size()),
    t0068::name);
