#include "0988.hpp"
#include "leet_code_binary_tree.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::smallestFromLeaf;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[0,1,2,3,4,3,4] "dba"

[25,1,3,1,3,0,2] "adz"

[25,0,null,1,null,0,0,1,null,null,null,0] "ababaz"
)cases");

using t0988 = SolutionTests<Solution>;

TEST_P(t0988, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.smallestFromLeaf(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t0988,
    t0988::parameters(kCases.size()),
    t0988::name);
