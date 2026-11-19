#include "0199.hpp"
#include "leet_code_binary_tree.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::rightSideView;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[1,2,3,4,null,null,null,5] [1,3,4,5]
)cases");

using t0199 = SolutionTests<Solution>;

TEST_P(t0199, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.rightSideView(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0199,
    t0199::parameters(kCases.size()),
    t0199::name);
