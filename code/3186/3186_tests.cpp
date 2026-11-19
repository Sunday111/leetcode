#include "3186.hpp"
#include "solution_tests.hpp"
#include "test_cases_helpers.hpp"

static constexpr auto kMethodToTest = &Solution::maximumTotalDamage;
static const auto kCases = parse_test_cases<kMethodToTest>(R"cases(
[7,1,6,6] 13

[3,4,5,6,6,7,1,1,1,1,1,9,9,9,9,9,9,9,9,9,6] 104
)cases");

using t3186 = SolutionTests<Solution>;

TEST_P(t3186, Test)
{
    check(
        kCases,
        [](auto& solution, auto&... args)
        { return solution.maximumTotalDamage(args...); });
}

INSTANTIATE_TEST_SUITE_P(
    Gen,
    t3186,
    t3186::parameters(kCases.size()),
    t3186::name);
