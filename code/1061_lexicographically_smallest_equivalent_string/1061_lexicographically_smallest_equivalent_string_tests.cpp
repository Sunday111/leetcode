#include "1061_lexicographically_smallest_equivalent_string.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::smallestEquivalentString;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"parker" "morris" "parser" "makkek"
)cases");

using t1061_lexicographically_smallest_equivalent_string =
    SolutionTests<Solution>;

TEST_P(t1061_lexicographically_smallest_equivalent_string, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.smallestEquivalentString(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1061_lexicographically_smallest_equivalent_string,
    t1061_lexicographically_smallest_equivalent_string::parameters(
        kCases.size()),
    t1061_lexicographically_smallest_equivalent_string::name);
