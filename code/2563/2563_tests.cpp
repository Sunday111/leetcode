#include "2563.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::countFairPairs;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[0,1,7,4,4,5] 3 6 6
)cases");

using t2563 = SolutionTests<Solution>;

TEST_P(t2563, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.countFairPairs(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t2563,
    t2563::parameters(kCases.size()),
    t2563::name);
