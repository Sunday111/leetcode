#include "0052.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::totalNQueens;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
4 2
)cases");

using t0052 = SolutionTests<Solution>;

TEST_P(t0052, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.totalNQueens(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0052,
    t0052::parameters(kCases.size()),
    t0052::name);
