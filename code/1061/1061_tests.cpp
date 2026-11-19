#include "1061.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::smallestEquivalentString;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"parker" "morris" "parser" "makkek"
)cases");

using t1061 = SolutionTests<Solution>;

TEST_P(t1061, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.smallestEquivalentString(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1061,
    t1061::parameters(kCases.size()),
    t1061::name);
