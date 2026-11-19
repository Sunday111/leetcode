#include "0064_minimum_path_sum_2.hpp"
#include "parse_2d_array.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::minPathSum;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[[1,3,1],[1,5,1],[4,2,1]] 7

[[1,2,3],[4,5,6]] 12
)cases");

using t0064_minimum_path_sum_2 = SolutionTests<Solution>;

TEST_P(t0064_minimum_path_sum_2, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.minPathSum(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0064_minimum_path_sum_2,
    t0064_minimum_path_sum_2::parameters(kCases.size()),
    t0064_minimum_path_sum_2::name);
