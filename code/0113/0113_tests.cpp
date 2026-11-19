#include "0113.hpp"
#include "leet_code_binary_tree.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::binaryTreePaths;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[5,4,8,11,null,13,4,7,2,null,null,5,1] 22 [[5,4,11,2],[5,8,4,5]]
)cases");

using t0113_path_sum_2 = SolutionTests<Solution>;

TEST_P(t0113_path_sum_2, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.binaryTreePaths(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0113_path_sum_2,
    t0113_path_sum_2::parameters(kCases.size()),
    t0113_path_sum_2::name);
