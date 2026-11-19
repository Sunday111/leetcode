#include "3847.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::scoreDifference;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[1,2,3] 0

[2,4,2,1,2,1] 4

[1] -1
)cases");

using t3847 = SolutionTests<Solution>;

TEST_P(t3847, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.scoreDifference(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3847,
    t3847::parameters(kCases.size()),
    t3847::name);
