#include "0279.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::numSquares;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
12 3

13 2

1 1

7168 4

7217 3
)cases");

using t0279_perfect_squares = SolutionTests<Solution>;

TEST_P(t0279_perfect_squares, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.numSquares(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0279_perfect_squares,
    t0279_perfect_squares::parameters(kCases.size()),
    t0279_perfect_squares::name);
