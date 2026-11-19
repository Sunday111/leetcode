#include "2761.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::findPrimePairs;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
10 [[3,7],[5,5]]

2 []

100 [[3,97],[11,89],[17,83],[29,71],[41,59],[47,53]]
)cases");

using t2761 = SolutionTests<Solution>;

TEST_P(t2761, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.findPrimePairs(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2761,
    t2761::parameters(kCases.size()),
    t2761::name);
