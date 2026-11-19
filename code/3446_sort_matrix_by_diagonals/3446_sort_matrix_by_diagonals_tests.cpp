#include <print>

#include "3446_sort_matrix_by_diagonals.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::sortMatrix;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[[1,7,3],[9,8,2],[4,5,6]] [[8,2,3],[9,6,7],[4,5,1]]
)cases");

using t3446_sort_matrix_by_diagonals = SolutionTests<Solution>;

TEST_P(t3446_sort_matrix_by_diagonals, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.sortMatrix(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3446_sort_matrix_by_diagonals,
    t3446_sort_matrix_by_diagonals::parameters(kCases.size()),
    t3446_sort_matrix_by_diagonals::name);
