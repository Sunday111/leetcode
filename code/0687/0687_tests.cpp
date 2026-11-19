#include "0687.hpp"
#include "leet_code_binary_tree.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::longestUnivaluePath;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[5,4,5,1,1,null,5] 2

[1,null,1,1,1,1,1,1] 4
)cases");

using t0687 = SolutionTests<Solution>;

TEST_P(t0687, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.longestUnivaluePath(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0687,
    t0687::parameters(kCases.size()),
    t0687::name);
