#include "0257.hpp"
#include "leet_code_binary_tree.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::binaryTreePaths;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[1,2,3,null,5] ["1->2->5","1->3"]
)cases");

using t0257 = SolutionTests<Solution>;

TEST_P(t0257, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.binaryTreePaths(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0257,
    t0257::parameters(kCases.size()),
    t0257::name);
