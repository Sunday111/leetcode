#include "0096.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::numTrees;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
1 1

2 2

3 5

4 14

5 42

6 132

7 429

8 1430

19 1767263190
)cases");

using t0096 = SolutionTests<Solution>;

TEST_P(t0096, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.numTrees(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0096,
    t0096::parameters(kCases.size()),
    t0096::name);
