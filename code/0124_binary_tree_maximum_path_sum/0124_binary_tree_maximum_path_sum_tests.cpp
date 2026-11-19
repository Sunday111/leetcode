#include <cassert>

#include "0124_binary_tree_maximum_path_sum.hpp"
#include "leet_code_binary_tree.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::maxPathSum;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[1,2,3] 6

[-10,9,20,null,null,15,7] 42

[-2,-1] -1
)cases");

using t0124_binary_tree_maximum_path_sum = SolutionTests<Solution>;

TEST_P(t0124_binary_tree_maximum_path_sum, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.maxPathSum(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0124_binary_tree_maximum_path_sum,
    t0124_binary_tree_maximum_path_sum::parameters(kCases.size()),
    t0124_binary_tree_maximum_path_sum::name);
