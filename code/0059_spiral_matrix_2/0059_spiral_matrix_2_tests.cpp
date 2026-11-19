#include "0059_spiral_matrix_2.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::generateMatrix;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
3 [[1,2,3],[8,9,4],[7,6,5]]
)cases");

using t0059_spiral_matrix_2 = SolutionTests<Solution>;

TEST_P(t0059_spiral_matrix_2, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.generateMatrix(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0059_spiral_matrix_2,
    t0059_spiral_matrix_2::parameters(kCases.size()),
    t0059_spiral_matrix_2::name);
