#include "3333.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::possibleStringCount;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"aabbccdd" 7 5

"aaabbb" 3 8

"d" 1 1
)cases");

using t3333 = SolutionTests<Solution>;

TEST_P(t3333, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.possibleStringCount(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3333,
    t3333::parameters(kCases.size()),
    t3333::name);
