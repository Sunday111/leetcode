#include "1975_maximum_matrix_sum.hpp"
#include "parse_2d_array.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::maxMatrixSum;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[[1,-1],[-1,1]] 4

[[1,2,3],[-1,-2,-3],[1,2,3]] 16

[[2,9,3],[5,4,-4],[1,7,1]] 34

[[-10000,-10000,-10000],[-10000,-10000,-10000],[-10000,-10000,-10000]] 70000
)cases");

using t1975_maximum_matrix_sum = SolutionTests<Solution>;

TEST_P(t1975_maximum_matrix_sum, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.maxMatrixSum(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t1975_maximum_matrix_sum,
    t1975_maximum_matrix_sum::parameters(kCases.size()),
    t1975_maximum_matrix_sum::name);
