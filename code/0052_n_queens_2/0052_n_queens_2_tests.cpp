#include "0052_n_queens_2.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::totalNQueens;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
4 2
)cases");

using t0052_n_queens_2 = SolutionTests<Solution>;

TEST_P(t0052_n_queens_2, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.totalNQueens(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0052_n_queens_2,
    t0052_n_queens_2::parameters(kCases.size()),
    t0052_n_queens_2::name);
