#include "3363.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::maxCollectedFruits;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[[1,2,3,4],[5,6,8,7],[9,10,11,12],[13,14,15,16]] 100
)cases");

using t3363 = SolutionTests<Solution>;

TEST_P(t3363, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.maxCollectedFruits(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3363,
    t3363::parameters(kCases.size()),
    t3363::name);
