#include "0965_univalued_binary_tree.hpp"
#include "leet_code_binary_tree.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::isUnivalTree;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[1,1,1,1,1,null,1] true

[1,100] false
)cases");

using t0965_univalued_binary_tree = SolutionTests<Solution>;

TEST_P(t0965_univalued_binary_tree, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.isUnivalTree(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0965_univalued_binary_tree,
    t0965_univalued_binary_tree::parameters(kCases.size()),
    t0965_univalued_binary_tree::name);
