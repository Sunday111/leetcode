#include "3713.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::longestBalanced;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
"abbac" 4

"nlllk" 3
)cases");

using t3713 = SolutionTests<Solution>;

TEST_P(t3713, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.longestBalanced(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3713,
    t3713::parameters(kCases.size()),
    t3713::name);
