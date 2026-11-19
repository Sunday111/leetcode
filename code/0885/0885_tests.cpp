#include "0885.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::spiralMatrixIII;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
1 4 0 0 [[0,0],[0,1],[0,2],[0,3]]
)cases");

using t0885_spiral_matrix_3 = SolutionTests<Solution>;

TEST_P(t0885_spiral_matrix_3, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.spiralMatrixIII(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0885_spiral_matrix_3,
    t0885_spiral_matrix_3::parameters(kCases.size()),
    t0885_spiral_matrix_3::name);
