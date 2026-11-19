#include "0543_diameter_of_binary_tree.hpp"
#include "leet_code_binary_tree.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::diameterOfBinaryTree;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[1,2,3,4,5] 3

[1,2] 1
)cases");

using t0543_diameter_of_binary_tree = SolutionTests<Solution>;

TEST_P(t0543_diameter_of_binary_tree, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.diameterOfBinaryTree(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0543_diameter_of_binary_tree,
    t0543_diameter_of_binary_tree::parameters(kCases.size()),
    t0543_diameter_of_binary_tree::name);
