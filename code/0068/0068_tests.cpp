#include "0068.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::fullJustify;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
["This","is","an","example","of","text","justification."]
16
["This    is    an","example  of text","justification.  "]
)cases");

using t0068_text_justification = SolutionTests<Solution>;

TEST_P(t0068_text_justification, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.fullJustify(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0068_text_justification,
    t0068_text_justification::parameters(kCases.size()),
    t0068_text_justification::name);
