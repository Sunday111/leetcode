#include "0950.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::deckRevealedIncreasing;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[17,13,11,2,3,5,7] [2,13,3,11,5,17,7]
)cases");

using t0950 = SolutionTests<Solution>;

TEST_P(t0950, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.deckRevealedIncreasing(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0950,
    t0950::parameters(kCases.size()),
    t0950::name);
